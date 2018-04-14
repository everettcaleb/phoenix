#include "EventManager.h"

//========================================================================================================

EventManager::EventManager()
{
    activeQueue_ = 0;
    firstEvent_[0] = 0;
    firstEvent_[1] = 0;
    lastEvent_[0] = 0;
    lastEvent_[1] = 0;
    firstNode_ = 0;
    lastNode_ = 0;
}

//========================================================================================================

EventManager::~EventManager()
{
    //Clear event queues
    for (int i = 0; i < 2; ++i)
    {
        lastEvent_[i] = firstEvent_[i];
        while (lastEvent_[i] != 0)
        {
            if (lastEvent_[i]->finalizer)
            {
                lastEvent_[i]->finalizer(lastEvent_[i]->data);
            }
            firstEvent_[i] = lastEvent_[i]->next;
            delete lastEvent_[i];
            lastEvent_[i] = firstEvent_[i];
        }
    }

    //Clear subscribers
    lastNode_ = firstNode_;
    while (lastNode_ != 0)
    {
        firstNode_ = lastNode_->next;
        delete lastNode_;
        lastNode_ = firstNode_;
    }
}

//========================================================================================================

void EventManager::registerSubscriber(IEventSubscriber *subscriber)
{
    EventSubscriberNode *node = new EventSubscriberNode;
    node->subscriber = subscriber;
    node->next = 0;

    //First one
    if (firstNode_ == 0)
    {
        firstNode_ = node;
        lastNode_ = node;
    }
    //Other
    else
    {
        lastNode_->next = node;
        lastNode_ = node;
    }
}

//========================================================================================================

void EventManager::unregisterSubscriber(IEventSubscriber *subscriber)
{
    EventSubscriberNode *prevNode = 0;
    EventSubscriberNode *node = firstNode_;
    while (node != 0) 
    {
        if (node->subscriber == subscriber)
        {
            //First one
            if (prevNode == 0) 
            {
                firstNode_ = node->next;
            }
            //Last one
            else if (node->next == 0)
            {
                prevNode->next = 0;
                lastNode_ = prevNode;
            }
            //Other
            else
            {
                prevNode->next = node->next;
            }

            delete node;
            return;
        }
        prevNode = node;
        node = node->next;
    }
}

//========================================================================================================

void EventManager::publishEvent(EVID eventId, void *data)
{
    EventSubscriberNode *node = firstNode_;
    while (node != 0)
    {
        node->subscriber->handleEvent(eventId, data);
        node = node->next;
    }
}

//========================================================================================================

void EventManager::queueEvent(EVID eventId, void *data, EventDataFinalizer finalizer)
{
    QueuedEvent *ev = new QueuedEvent;
    ev->eventId = eventId;
    ev->data = data;
    ev->finalizer = finalizer;
    ev->next = 0;

    //First one
    if (firstEvent_[activeQueue_] == 0)
    {
        firstEvent_[activeQueue_] = ev;
        lastEvent_[activeQueue_] = ev;
    }
    //Other
    else
    {
        lastEvent_[activeQueue_]->next = ev;
        lastEvent_[activeQueue_] = ev;
    }
}

//========================================================================================================

void EventManager::publishQueuedEvents()
{
    int publishQueue = activeQueue_;
    activeQueue_ = (++activeQueue_ % 2);

    QueuedEvent *ev = firstEvent_[publishQueue];
    QueuedEvent *ev2;
    
    while (ev != 0)
    {
        publishEvent(ev->eventId, ev->data);

        if (ev->finalizer)
        {
            ev->finalizer(ev->data);
        }

        ev2 = ev->next;
        delete ev;
        ev = ev2;
    }

    firstEvent_[publishQueue] = 0;
    lastEvent_[publishQueue] = 0;
}

//========================================================================================================

void DefaultHeapEventDataFinalizer(void *data)
{
    delete data;
}