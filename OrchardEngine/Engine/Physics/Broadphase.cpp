#include "Broadphase.hpp"

using namespace orchard;

std::vector<BroadphasePair> Broadphase::computePairs(const std::vector<RigidBody>& bodies) {
    std::vector<BroadphasePair> pairs;
    for (size_t i = 0; i < bodies.size(); ++i) {
        for (size_t j = i + 1; j < bodies.size(); ++j) {
            const auto& a = bodies[i];
            const auto& b = bodies[j];
            simd_float3 amin = a.position - a.halfExtents;
            simd_float3 amax = a.position + a.halfExtents;
            simd_float3 bmin = b.position - b.halfExtents;
            simd_float3 bmax = b.position + b.halfExtents;
            bool overlap = (amin.x <= bmax.x && amax.x >= bmin.x) &&
                           (amin.y <= bmax.y && amax.y >= bmin.y) &&
                           (amin.z <= bmax.z && amax.z >= bmin.z);
            if (overlap) {
                pairs.push_back({i, j});
            }
        }
    }
    return pairs;
}
