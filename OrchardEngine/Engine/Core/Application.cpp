#include "Application.hpp"
#include "Logging.hpp"
#include "../Platform/macOS/MacWindow.hpp"

using namespace orchard;

Application::Application(const ApplicationDescriptor& descriptor)
: m_descriptor(descriptor) {
    m_renderer = Renderer::Create(descriptor.width, descriptor.height, descriptor.enableRayTracing);
    m_world = std::make_unique<World>();
    m_physics = std::make_unique<PhysicsWorld>();
    m_audio = std::make_unique<AudioSystem>();
}

Application::~Application() {
    onShutdown();
}

void Application::run() {
    onStartup();
    double accumulator = 0.0;
    const double fixedDt = 1.0 / 120.0;

    while (m_running) {
        double dt = m_clock.tick();
        accumulator += dt;

        m_audio->process();

        while (accumulator >= fixedDt) {
            m_physics->step(static_cast<float>(fixedDt));
            accumulator -= fixedDt;
        }

        onUpdate(static_cast<float>(dt));
        m_renderer->render(*m_world);
        onRender();
    }
}

void Application::requestQuit() { m_running = false; }

void Application::onStartup() {
    ORCHARD_LOG_INFO("Application startup: {}", m_descriptor.appName);
}

void Application::onShutdown() {
    ORCHARD_LOG_INFO("Application shutdown");
}

void Application::onUpdate(float) {}

void Application::onRender() {}
