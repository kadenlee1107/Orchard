#pragma once

#include "../Entity.hpp"
#include "../../Math/MathTypes.hpp"

namespace orchard {

struct TransformComponent {
    Transform transform = Transform::identity();
    simd_float4x4 matrix = matrix_identity_float4x4;
    Entity parent = kInvalidEntity;
};

}
