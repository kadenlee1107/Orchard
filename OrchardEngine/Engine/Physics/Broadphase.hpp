#pragma once

#include <vector>
#include "RigidBody.hpp"

namespace orchard {

struct BroadphasePair {
    size_t a;
    size_t b;
};

class Broadphase {
public:
    std::vector<BroadphasePair> computePairs(const std::vector<RigidBody>& bodies);
};

}
