#pragma once

#include <simd/simd.h>
#include <cmath>

namespace orchard {

struct alignas(16) float3x3 {
    simd_float3 columns[3];
};

struct alignas(16) Transform {
    simd_float4x4 matrix;
    simd_float3 position;
    simd_quatf rotation;
    simd_float3 scale;

    static Transform identity() {
        Transform t;
        t.position = {0, 0, 0};
        t.rotation = simd_quaternion(0, 0, 0, 1);
        t.scale = {1, 1, 1};
        t.matrix = matrix_identity_float4x4;
        return t;
    }

    simd_float4x4 buildMatrix() const {
        simd_float4x4 T = matrix_identity_float4x4;
        T.columns[3] = simd_make_float4(position, 1.0f);
        simd_float4x4 R = simd_matrix4x4(rotation);
        simd_float4x4 S = matrix_identity_float4x4;
        S.columns[0].x = scale.x;
        S.columns[1].y = scale.y;
        S.columns[2].z = scale.z;
        return simd_mul(T, simd_mul(R, S));
    }
};

}
