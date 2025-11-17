#include "Renderer.hpp"
#include "Metal/MetalRenderer.hpp"

using namespace orchard;

std::unique_ptr<Renderer> Renderer::Create(uint32_t width, uint32_t height, bool enableRayTracing) {
    return std::make_unique<MetalRenderer>(width, height, enableRayTracing);
}
