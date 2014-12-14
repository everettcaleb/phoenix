#pragma once
#ifndef INCLUDE_PHOENIX_EVENTMANAGER_H
#define INCLUDE_PHOENIX_EVENTMANAGER_H

#include "EventSubscriberNode.h"
#include "EVID.h"
#include "IEventSubscriber.h"

typedef void(*EventDataFinalizer)(void *data);

class EventManager 
{
private:
    struct QueuedEvent
    {
        EVID eventId;
        void *data;
        EventDataFinalizer finalizer;
        QueuedEvent *next;
    };

    int activeQueue_;

    QueuedEvent *firstEvent_[2];
    QueuedEvent *lastEvent_[2];

    EventSubscriberNode *firstNode_;
    EventSubscriberNode *lastNode_;

    EventManager();
    EventManager(const EventManager& other) {}

public:
    ~EventManager();

    void registerSubscriber(IEventSubscriber *subscriber);

    void unregisterSubscriber(IEventSubscriber *subscriber);

    void publishEvent(EVID eventId, void *data);

    void queueEvent(EVID eventId, void *data, EventDataFinalizer finalizer);

    void publishQueuedEvents();

    inline static EventManager *create() { return new EventManager; }
};

#define DefaultNullEventDataFinalizer 0
void DefaultHeapEventDataFinalizer(void *data);

#endif //INCLUDE_PHOENIX_EVENTMANAGER_H