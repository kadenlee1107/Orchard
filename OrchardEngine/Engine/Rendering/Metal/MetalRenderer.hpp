#pragma once

#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>
#include <memory>
#include <unordered_map>
#include "../../Math/MathTypes.hpp"
#include "../../Resources/ResourceManager.hpp"
#include "../../ECS/World.hpp"
#include "../Renderer.hpp"
#include "../../Utils/Threading.hpp"

namespace orchard {

struct FrameState {
    id<MTLCommandBuffer> commandBuffer;
    id<MTLRenderCommandEncoder> gbufferEncoder;
    id<MTLRenderCommandEncoder> lightingEncoder;
    id<MTLComputeCommandEncoder> cullingEncoder;
};

class MetalRenderer final : public Renderer {
public:
    MetalRenderer(uint32_t width, uint32_t height, bool enableRayTracing);
    ~MetalRenderer();

    void resize(uint32_t width, uint32_t height) override;
    void render(World& world) override;

private:
    void createDevice();
    void createPipelines(bool enableRayTracing);
    void createDepthTargets(uint32_t width, uint32_t height);
    void uploadScene(World& world);

    id<MTLDevice> m_device = nil;
    id<MTLCommandQueue> m_commandQueue = nil;
    MTKView* m_view = nil;
    id<MTLLibrary> m_library = nil;

    id<MTLTexture> m_depthTexture = nil;
    id<MTLTexture> m_hdrTarget = nil;

    id<MTLRenderPipelineState> m_gbufferPipeline = nil;
    id<MTLRenderPipelineState> m_lightingPipeline = nil;
    id<MTLComputePipelineState> m_clusterCullPipeline = nil;
    id<MTLComputePipelineState> m_metalfxPipeline = nil;
    id<MTLAccelerationStructure> m_tlas = nil;

    dispatch_semaphore_t m_inFlightSemaphore;
};

}
