#include "PhysicsWorld.hpp"

using namespace orchard;

PhysicsWorld::PhysicsWorld() {
    m_bodies.reserve(256);
}

RigidBody& PhysicsWorld::createRigidBody(const RigidBodyDesc& desc) {
    RigidBody body{};
    body.position = desc.position;
    body.mass = desc.mass;
    body.halfExtents = desc.halfExtents;
    body.dynamic = desc.dynamic;
    m_bodies.push_back(body);
    return m_bodies.back();
}

void PhysicsWorld::step(float dt) {
    auto pairs = m_broadphase.computePairs(m_bodies);
    auto contacts = m_narrowphase.collide(m_bodies, pairs);

    for (auto& body : m_bodies) {
        if (!body.dynamic) continue;
        body.velocity += simd_make_float3(0, -9.81f, 0) * dt;
        body.position += body.velocity * dt;
    }

    for (const auto& contact : contacts) {
        RigidBody& a = m_bodies[contact.bodyA];
        RigidBody& b = m_bodies[contact.bodyB];
        if (!a.dynamic && !b.dynamic) continue;
        simd_float3 correction = contact.normal * contact.penetration * 0.5f;
        if (a.dynamic) {
            a.position -= correction;
            a.velocity = simd_make_float3(0);
        }
        if (b.dynamic) {
            b.position += correction;
            b.velocity = simd_make_float3(0);
        }
    }
}
