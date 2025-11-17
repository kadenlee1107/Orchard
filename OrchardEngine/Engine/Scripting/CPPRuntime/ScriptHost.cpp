#include "ScriptHost.hpp"

using namespace orchard;

void ScriptHost::registerSwiftCallback(const std::string& symbol, SwiftCallback cb) {
    m_callbacks[symbol] = std::move(cb);
}

void ScriptHost::callSwift(const std::string& symbol, const std::string& payload) {
    auto it = m_callbacks.find(symbol);
    if (it != m_callbacks.end()) {
        it->second(payload);
    }
}
