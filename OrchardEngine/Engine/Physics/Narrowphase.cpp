#include "Narrowphase.hpp"

using namespace orchard;

std::vector<ContactPoint> Narrowphase::collide(const std::vector<RigidBody>& bodies, const std::vector<BroadphasePair>& pairs) {
    std::vector<ContactPoint> contacts;
    for (auto& pair : pairs) {
        const auto& a = bodies[pair.a];
        const auto& b = bodies[pair.b];
        simd_float3 delta = b.position - a.position;
        float distance = simd_length(delta);
        float radius = simd_length(a.halfExtents) + simd_length(b.halfExtents);
        float penetration = radius - distance;
        if (penetration > 0.0f) {
            ContactPoint cp;
            cp.normal = distance > 0.0f ? delta / distance : simd_make_float3(0, 1, 0);
            cp.penetration = penetration;
            cp.bodyA = pair.a;
            cp.bodyB = pair.b;
            contacts.push_back(cp);
        }
    }
    return contacts;
}
