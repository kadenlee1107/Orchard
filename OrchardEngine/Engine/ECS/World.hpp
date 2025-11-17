#pragma once

#include <any>
#include <functional>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include "Entity.hpp"
#include "Component.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/RenderComponents.hpp"

namespace orchard {

class World {
public:
    World();

    Entity createEntity();
    void destroyEntity(Entity entity);

    template <typename T, typename... Args>
    T& addComponent(Entity entity, Args&&... args) {
        auto& storage = storageFor<T>();
        T component(std::forward<Args>(args)...);
        auto [it, inserted] = storage.emplace(entity, std::move(component));
        (void)inserted;
        return it->second;
    }

    template <typename T>
    T& getComponent(Entity entity) {
        auto& storage = storageFor<T>();
        return storage.at(entity);
    }

    template <typename T>
    bool hasComponent(Entity entity) const {
        const auto& storage = storageForConst<T>();
        return storage.find(entity) != storage.end();
    }

    template <typename... Components>
    std::vector<Entity> view() {
        std::vector<Entity> result;
        for (Entity e : m_entities) {
            if ((hasComponent<Components>(e) && ...)) {
                result.push_back(e);
            }
        }
        return result;
    }

    void syncTransforms();

private:
    template <typename T>
    std::unordered_map<Entity, T>& storageFor() {
        auto it = m_componentStores.find(typeid(T));
        if (it == m_componentStores.end()) {
            it = m_componentStores.emplace(typeid(T), std::unordered_map<Entity, T>{}).first;
        }
        return std::any_cast<std::unordered_map<Entity, T>&>(it->second);
    }

    template <typename T>
    const std::unordered_map<Entity, T>& storageForConst() const {
        auto it = m_componentStores.find(typeid(T));
        if (it == m_componentStores.end()) {
            static std::unordered_map<Entity, T> empty;
            return empty;
        }
        return std::any_cast<const std::unordered_map<Entity, T>&>(it->second);
    }

    std::vector<Entity> m_entities;
    Entity m_nextEntity = 1;
    mutable std::unordered_map<std::type_index, std::any> m_componentStores;
};

}
