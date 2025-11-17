#pragma once

#include <Metal/Metal.hpp>
#include <simd/simd.h>
#include "../Entity.hpp"

namespace orchard {

struct RenderMeshComponent {
    id<MTLBuffer> vertexBuffer = nil;
    id<MTLBuffer> indexBuffer = nil;
    uint32_t indexCount = 0;
};

struct CameraComponent {
    float fov = 60.0f;
    float nearPlane = 0.01f;
    float farPlane = 1000.0f;
};

struct LightComponent {
    simd_float3 color = {1.0f, 1.0f, 1.0f};
    float intensity = 1.0f;
    bool castsShadow = true;
};

}
