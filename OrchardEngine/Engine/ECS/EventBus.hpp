#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

namespace orchard {

using EventId = uint32_t;

struct EventHeader {
    EventId id;
};

class EventBus {
public:
    template <typename Event>
    void subscribe(std::function<void(const Event&)> callback) {
        auto id = typeId<Event>();
        auto& list = m_handlers[id];
        list.push_back([callback](const EventHeader& header) { callback(static_cast<const Event&>(header)); });
    }

    template <typename Event>
    void publish(const Event& event) {
        auto id = typeId<Event>();
        auto it = m_handlers.find(id);
        if (it == m_handlers.end()) {
            return;
        }
        for (auto& handler : it->second) {
            handler(event);
        }
    }

private:
    template <typename Event>
    static EventId typeId() {
        static EventId id = ++s_nextId;
        return id;
    }

    static inline EventId s_nextId = 0;
    std::unordered_map<EventId, std::vector<std::function<void(const EventHeader&)>>> m_handlers;
};

}
