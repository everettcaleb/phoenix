#pragma once
#ifndef INCLUDE_PHOENIX_IEVENTSUBSCRIBER_H
#define INCLUDE_PHOENIX_IEVENTSUBSCRIBER_H

#include "EVID.h"

class IEventSubscriber
{
private:
    IEventSubscriber(const IEventSubscriber& other) {}

protected:
    IEventSubscriber() {}

public:
    virtual ~IEventSubscriber() {}

    virtual void HandleEvent(EVID eventId, void *data) = 0;
};

#endif //INCLUDE_PHOENIX_IEVENTSUBSCRIBER_H