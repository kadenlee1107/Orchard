# Rendering Pipeline

1. **Scene Upload**: ECS render systems sync transforms and update GPU buffers.
2. **Depth + GBuffer**: `gbufferVertex/gbufferFragment` write HDR targets and depth for clustered lighting.
3. **Lighting**: `lightingTileKernel` performs Forward+ tiled lighting with SSAO/SSR hooks.
4. **Ray Tracing**: Optional acceleration structures feed Metal ray tracing shaders for shadows/reflections.
5. **Post**: Tone-mapping, MetalFX upscaling, and compositing to the swapchain respect ProMotion + HDR/EDR targets.
6. **Presentation**: Renderer copies HDR target into MTKView drawable with adaptive sync metadata for XDR displays.
