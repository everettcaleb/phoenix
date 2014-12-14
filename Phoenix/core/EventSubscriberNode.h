#pragma once
#ifndef INCLUDE_PHOENIX_EVENTSUBSCRIBERNODE_H
#define INCLUDE_PHOENIX_EVENTSUBSCRIBERNODE_H

#include "IEventSubscriber.h"

struct EventSubscriberNode
{
    IEventSubscriber *subscriber;
    EventSubscriberNode *next;
};

#endif //INCLUDE_PHOENIX_EVENTSUBSCRIBERNODE_H