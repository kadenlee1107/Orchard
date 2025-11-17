#pragma once

#include <string>
#include <unordered_map>
#include <functional>

namespace orchard {

class ScriptHost {
public:
    using SwiftCallback = std::function<void(const std::string&)>;

    void registerSwiftCallback(const std::string& symbol, SwiftCallback cb);
    void callSwift(const std::string& symbol, const std::string& payload);

private:
    std::unordered_map<std::string, SwiftCallback> m_callbacks;
};

}
