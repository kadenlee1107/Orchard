#pragma once

#include <typeindex>
#include <unordered_map>

namespace orchard {

struct ComponentInfo {
    size_t size;
    size_t alignment;
};

class ComponentRegistry {
public:
    template <typename T>
    void registerComponent() {
        std::type_index idx(typeid(T));
        m_components[idx] = {sizeof(T), alignof(T)};
    }

    const ComponentInfo* info(std::type_index idx) const {
        auto it = m_components.find(idx);
        return it == m_components.end() ? nullptr : &it->second;
    }

private:
    std::unordered_map<std::type_index, ComponentInfo> m_components;
};

}
