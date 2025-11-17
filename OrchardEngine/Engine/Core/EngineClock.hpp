#pragma once

#include <chrono>

namespace orchard {

class EngineClock {
public:
    EngineClock() : m_last(std::chrono::high_resolution_clock::now()) {}

    double tick() {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> delta = now - m_last;
        m_last = now;
        return delta.count();
    }

private:
    std::chrono::high_resolution_clock::time_point m_last;
};

}
