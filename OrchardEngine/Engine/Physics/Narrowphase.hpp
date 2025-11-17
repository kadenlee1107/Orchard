#pragma once

#include <vector>
#include "RigidBody.hpp"
#include "Broadphase.hpp"

namespace orchard {

struct ContactPoint {
    simd_float3 normal;
    float penetration;
    size_t bodyA;
    size_t bodyB;
};

class Narrowphase {
public:
    std::vector<ContactPoint> collide(const std::vector<RigidBody>& bodies, const std::vector<BroadphasePair>& pairs);
};

}
