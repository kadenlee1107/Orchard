#pragma once

#include <memory>
#include <string>
#include <vector>
#include "EngineClock.hpp"
#include "../Rendering/Renderer.hpp"
#include "../ECS/World.hpp"
#include "../Physics/PhysicsWorld.hpp"
#include "../Audio/AudioSystem.hpp"

namespace orchard {

struct ApplicationDescriptor {
    std::string appName;
    uint32_t width = 1920;
    uint32_t height = 1080;
    bool enableValidation = false;
    bool enableRayTracing = true;
};

class Application {
public:
    explicit Application(const ApplicationDescriptor& descriptor);
    virtual ~Application();

    void run();
    void requestQuit();

    Renderer& renderer() { return *m_renderer; }
    World& world() { return *m_world; }
    PhysicsWorld& physics() { return *m_physics; }
    AudioSystem& audio() { return *m_audio; }

protected:
    virtual void onStartup();
    virtual void onShutdown();
    virtual void onUpdate(float dt);
    virtual void onRender();

private:
    ApplicationDescriptor m_descriptor;
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<World> m_world;
    std::unique_ptr<PhysicsWorld> m_physics;
    std::unique_ptr<AudioSystem> m_audio;
    EngineClock m_clock;
    bool m_running = true;
};

}
