#pragma once

#include <memory>
#include <vector>
#include <cstdint>
#include "../ECS/World.hpp"

namespace orchard {

class Renderer {
public:
    virtual ~Renderer() = default;
    virtual void resize(uint32_t width, uint32_t height) = 0;
    virtual void render(World& world) = 0;

    static std::unique_ptr<Renderer> Create(uint32_t width, uint32_t height, bool enableRayTracing);
};

}
