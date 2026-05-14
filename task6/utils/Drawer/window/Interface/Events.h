//
// Created by xac1k on 5/7/26.
//

#ifndef MAIN_EVENTS_H
#define MAIN_EVENTS_H
#include <typeindex>

class IEvent {
public:
    virtual ~IEvent() = default;
    virtual std::type_index getType() const = 0;
};

#define DECLARE_EVENT_TYPE(EventClass) \
    std::type_index getType() const override { return typeid(EventClass); }


#endif //MAIN_EVENTS_H
