#import "MetalRenderer.hpp"
#import <QuartzCore/CAMetalLayer.h>
#include "../../Core/Logging.hpp"
#include "../../ECS/Systems/RenderSystems.hpp"

using namespace orchard;

MetalRenderer::MetalRenderer(uint32_t width, uint32_t height, bool enableRayTracing) {
    createDevice();
    createDepthTargets(width, height);
    createPipelines(enableRayTracing);
    m_inFlightSemaphore = dispatch_semaphore_create(3);
}

MetalRenderer::~MetalRenderer() {
    m_depthTexture = nil;
    m_hdrTarget = nil;
}

void MetalRenderer::createDevice() {
    m_device = MTLCreateSystemDefaultDevice();
    m_commandQueue = [m_device newCommandQueue];
    NSError* error = nil;
    NSString* shaderPath = [[NSBundle mainBundle] pathForResource:@"Orchard" ofType:@"metallib"];
    if (shaderPath) {
        m_library = [m_device newLibraryWithFile:shaderPath error:&error];
    } else {
        m_library = [m_device newDefaultLibrary];
    }
    if (error) {
        ORCHARD_LOG_ERROR("Failed to load Metal library: %s", error.localizedDescription.UTF8String);
    }
}

void MetalRenderer::createDepthTargets(uint32_t width, uint32_t height) {
    MTLTextureDescriptor* depthDesc = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:MTLPixelFormatDepth32Float width:width height:height mipmapped:NO];
    depthDesc.storageMode = MTLStorageModePrivate;
    depthDesc.usage = MTLTextureUsageRenderTarget;
    m_depthTexture = [m_device newTextureWithDescriptor:depthDesc];

    MTLTextureDescriptor* hdrDesc = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:MTLPixelFormatRGBA16Float width:width height:height mipmapped:NO];
    hdrDesc.storageMode = MTLStorageModePrivate;
    hdrDesc.usage = MTLTextureUsageRenderTarget | MTLTextureUsageShaderRead;
    m_hdrTarget = [m_device newTextureWithDescriptor:hdrDesc];
}

void MetalRenderer::createPipelines(bool enableRayTracing) {
    NSError* error = nil;
    id<MTLFunction> vert = [m_library newFunctionWithName:@"gbufferVertex"];
    id<MTLFunction> frag = [m_library newFunctionWithName:@"gbufferFragment"];

    MTLRenderPipelineDescriptor* gdesc = [MTLRenderPipelineDescriptor new];
    gdesc.vertexFunction = vert;
    gdesc.fragmentFunction = frag;
    gdesc.colorAttachments[0].pixelFormat = MTLPixelFormatRGBA16Float;
    gdesc.depthAttachmentPixelFormat = MTLPixelFormatDepth32Float;
    m_gbufferPipeline = [m_device newRenderPipelineStateWithDescriptor:gdesc error:&error];
    if (error) {
        ORCHARD_LOG_ERROR("GBuffer pipeline creation failed: %s", error.localizedDescription.UTF8String);
    }

    id<MTLFunction> lightingKernel = [m_library newFunctionWithName:@"lightingTileKernel"];
    m_clusterCullPipeline = [m_device newComputePipelineStateWithFunction:lightingKernel error:&error];
    if (error) {
        ORCHARD_LOG_ERROR("Lighting pipeline creation failed: %s", error.localizedDescription.UTF8String);
    }

    if (enableRayTracing) {
        id<MTLFunction> rtFunc = [m_library newFunctionWithName:@"rayTraceShadows"];
        if (rtFunc) {
            MTLComputePipelineDescriptor* desc = [MTLComputePipelineDescriptor new];
            desc.computeFunction = rtFunc;
            m_metalfxPipeline = [m_device newComputePipelineStateWithDescriptor:desc options:0 reflection:nil error:&error];
        }
    }
}

void MetalRenderer::resize(uint32_t width, uint32_t height) {
    createDepthTargets(width, height);
}

void MetalRenderer::uploadScene(World& world) {
    world.syncTransforms();
}

void MetalRenderer::render(World& world) {
    dispatch_semaphore_wait(m_inFlightSemaphore, DISPATCH_TIME_FOREVER);
    id<CAMetalDrawable> drawable = [m_view currentDrawable];
    if (!drawable) {
        dispatch_semaphore_signal(m_inFlightSemaphore);
        return;
    }

    uploadScene(world);

    MTLRenderPassDescriptor* gpass = [MTLRenderPassDescriptor renderPassDescriptor];
    gpass.colorAttachments[0].texture = m_hdrTarget;
    gpass.colorAttachments[0].loadAction = MTLLoadActionClear;
    gpass.colorAttachments[0].clearColor = MTLClearColorMake(0.0, 0.0, 0.0, 1.0);
    gpass.colorAttachments[0].storeAction = MTLStoreActionStore;
    gpass.depthAttachment.texture = m_depthTexture;
    gpass.depthAttachment.loadAction = MTLLoadActionClear;
    gpass.depthAttachment.storeAction = MTLStoreActionDontCare;

    id<MTLCommandBuffer> cmd = [m_commandQueue commandBuffer];
    FrameState frame{cmd, nil, nil, nil};
    frame.commandBuffer = cmd;

    id<MTLRenderCommandEncoder> encoder = [cmd renderCommandEncoderWithDescriptor:gpass];
    frame.gbufferEncoder = encoder;

    for (auto entity : world.view<RenderMeshComponent, TransformComponent>()) {
        const auto& mesh = world.getComponent<RenderMeshComponent>(entity);
        const auto& transform = world.getComponent<TransformComponent>(entity);
        [encoder setRenderPipelineState:m_gbufferPipeline];
        [encoder setVertexBuffer:mesh.vertexBuffer offset:0 atIndex:0];
        [encoder setVertexBytes:&transform.matrix length:sizeof(transform.matrix) atIndex:1];
        [encoder drawIndexedPrimitives:MTLPrimitiveTypeTriangle indexCount:mesh.indexCount indexType:MTLIndexTypeUInt32 indexBuffer:mesh.indexBuffer indexBufferOffset:0];
    }
    [encoder endEncoding];

    id<MTLBlitCommandEncoder> blit = [cmd blitCommandEncoder];
    [blit copyFromTexture:m_hdrTarget sourceSlice:0 sourceLevel:0 sourceOrigin:MTLOriginMake(0, 0, 0) sourceSize:MTLSizeMake(m_hdrTarget.width, m_hdrTarget.height, 1) toTexture:drawable.texture destinationSlice:0 destinationLevel:0 destinationOrigin:MTLOriginMake(0, 0, 0)];
    [blit endEncoding];

    [cmd presentDrawable:drawable];
    [cmd addCompletedHandler:^(id<MTLCommandBuffer>) {
        dispatch_semaphore_signal(m_inFlightSemaphore);
    }];
    [cmd commit];
}
