#include "AudioSystem.hpp"
#include "../Core/Logging.hpp"

using namespace orchard;

AudioSystem::AudioSystem() {
    NewAUGraph(&m_graph);
    AUGraphOpen(m_graph);
    AUGraphInitialize(m_graph);
}

AudioSystem::~AudioSystem() {
    AUGraphStop(m_graph);
    DisposeAUGraph(m_graph);
}

void AudioSystem::process() {
    Boolean running = false;
    AUGraphIsRunning(m_graph, &running);
    if (!running) {
        AUGraphStart(m_graph);
    }
}

void AudioSystem::loadBank(const std::string& path) {
    ORCHARD_LOG_INFO("Loading audio bank: %s", path.c_str());
}

void AudioSystem::play(const AudioSourceDesc& desc) {
    ORCHARD_LOG_INFO("Play sound: %s spatial=%d", desc.path.c_str(), desc.spatial);
}
