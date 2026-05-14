//
// Created by xac1k on 5/7/26.
//

#ifndef MAIN_EVENTDISPATCHER_H
#define MAIN_EVENTDISPATCHER_H
#include <functional>
#include <memory>
#include <typeindex>

#include "Events.h"

class EventDispatcher {
public:
    template<typename T>
    using Handler = std::function<void(const T&)>;

    template<typename T>
    void Subscribe(Handler<T> handler) {
        auto& handlers = m_handlers[typeid(T)];
        auto ptrHandler = std::make_shared<Handler<T>>(std::move(handler));
        handlers.push_back(ptrHandler);
    }

    template<typename T>
    void Dispatch(const T& event) {
        auto it = m_handlers.find(typeid(T));
        if (it != m_handlers.end()) {
            for (auto& handlerPtr : it->second)
                CallHandler<T>(event, handlerPtr);
        }
    }

private:
    std::unordered_map<std::type_index, std::vector<std::shared_ptr<void>>> m_handlers;

    template<typename T>
    void CallHandler(const IEvent& event, const std::shared_ptr<void> handlerPtr) const {
        auto handler = std::static_pointer_cast<Handler<T>>(handlerPtr);
        if (*handler) {
            (*handler)(static_cast<const T&>(event));
        }
    }
};

#endif //MAIN_EVENTDISPATCHER_H