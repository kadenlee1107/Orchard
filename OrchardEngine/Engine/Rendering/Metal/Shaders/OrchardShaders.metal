#include <metal_stdlib>
using namespace metal;

struct VertexIn {
    float3 position [[attribute(0)]];
    float3 normal [[attribute(1)]];
    float2 uv [[attribute(2)]];
};

struct VertexOut {
    float4 position [[position]];
    float3 worldPos;
    float3 normal;
    float2 uv;
};

struct CameraData {
    float4x4 viewProj;
};

struct MaterialData {
    float4 baseColor;
};

vertex VertexOut gbufferVertex(VertexIn in [[stage_in]], constant float4x4& model [[buffer(1)]], constant CameraData& camera [[buffer(2)]]) {
    VertexOut out;
    float4 world = model * float4(in.position, 1.0);
    out.position = camera.viewProj * world;
    out.worldPos = world.xyz;
    out.normal = (model * float4(in.normal, 0.0)).xyz;
    out.uv = in.uv;
    return out;
}

fragment float4 gbufferFragment(VertexOut in [[stage_in]], constant MaterialData& material [[buffer(0)]]) {
    float3 normal = normalize(in.normal);
    float3 lightDir = normalize(float3(0.3, 0.8, 0.2));
    float NdotL = max(dot(normal, lightDir), 0.0);
    float3 color = material.baseColor.rgb * (0.2 + 0.8 * NdotL);
    return float4(color, 1.0);
}

kernel void lightingTileKernel(uint2 gid [[thread_position_in_grid]], texture2d<float, access::read> hdrInput [[texture(0)]], texture2d<float, access::write> hdrOutput [[texture(1)]]) {
    constexpr sampler linearSampler(address::clamp_to_edge, filter::linear);
    float2 uv = (float2(gid) + 0.5) / float2(hdrInput.get_width(), hdrInput.get_height());
    float4 color = hdrInput.sample(linearSampler, uv);
    hdrOutput.write(color, gid);
}

kernel void rayTraceShadows(uint2 gid [[thread_position_in_grid]]) {
    // Stub for ray traced shadows.
}
