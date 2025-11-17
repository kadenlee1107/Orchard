#pragma once

#include <AudioToolbox/AudioToolbox.h>
#include <vector>
#include <string>

namespace orchard {

struct AudioSourceDesc {
    std::string path;
    bool spatial = false;
};

class AudioSystem {
public:
    AudioSystem();
    ~AudioSystem();

    void process();
    void loadBank(const std::string& path);
    void play(const AudioSourceDesc& desc);

private:
    AUGraph m_graph = nullptr;
    AudioUnit m_mixer = nullptr;
};

}
