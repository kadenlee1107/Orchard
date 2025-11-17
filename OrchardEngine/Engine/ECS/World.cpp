#include "World.hpp"
#include <algorithm>

using namespace orchard;

World::World() {
    m_entities.reserve(1024);
}

Entity World::createEntity() {
    Entity entity = m_nextEntity++;
    m_entities.push_back(entity);
    return entity;
}

void World::destroyEntity(Entity entity) {
    m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end());
}

void World::syncTransforms() {
    for (auto& [type, storageAny] : m_componentStores) {
        if (type == typeid(TransformComponent)) {
            auto& storage = std::any_cast<std::unordered_map<Entity, TransformComponent>&>(storageAny);
            for (auto& [entity, transform] : storage) {
                transform.matrix = transform.transform.buildMatrix();
            }
        }
    }
}
