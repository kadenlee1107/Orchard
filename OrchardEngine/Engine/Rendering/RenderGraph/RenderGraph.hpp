#pragma once

#include <functional>
#include <string>
#include <vector>

namespace orchard {

class RenderGraph {
public:
    struct Pass {
        std::string name;
        std::function<void()> execute;
    };

    void addPass(const std::string& name, std::function<void()> execute);
    void execute();

private:
    std::vector<Pass> m_passes;
};

}
