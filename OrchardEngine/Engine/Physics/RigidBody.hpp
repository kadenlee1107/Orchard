#pragma once

#include <simd/simd.h>

namespace orchard {

struct RigidBodyDesc {
    simd_float3 position;
    float mass;
    simd_float3 halfExtents;
    bool dynamic;
};

struct RigidBody {
    simd_float3 position;
    simd_float3 velocity;
    float mass;
    simd_float3 halfExtents;
    bool dynamic;
};

}
