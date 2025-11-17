#include "RenderGraph.hpp"

using namespace orchard;

void RenderGraph::addPass(const std::string& name, std::function<void()> execute) {
    m_passes.push_back({name, execute});
}

void RenderGraph::execute() {
    for (auto& pass : m_passes) {
        pass.execute();
    }
}
