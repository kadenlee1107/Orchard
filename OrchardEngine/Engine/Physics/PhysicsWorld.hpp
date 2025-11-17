#pragma once

#include <vector>
#include "RigidBody.hpp"
#include "Broadphase.hpp"
#include "Narrowphase.hpp"

namespace orchard {

class PhysicsWorld {
public:
    PhysicsWorld();

    RigidBody& createRigidBody(const RigidBodyDesc& desc);
    void step(float dt);

private:
    Broadphase m_broadphase;
    Narrowphase m_narrowphase;
    std::vector<RigidBody> m_bodies;
};

}
