#pragma once
#ifndef INCLUDE_PHOENIX_COMPONENTNODE_H
#define INCLUDE_PHOENIX_COMPONENTNODE_H

#include "CUID.h"

typedef void(*ComponentFinalizer)(void *component);

struct ComponentNode
{
    CUID identifier;
    void *component;
    ComponentFinalizer finalizer;
    ComponentNode *previous;
};

#define DefaultNullComponentFinalizer 0
void DefaultHeapComponentFinalizer(void *component);

#endif //INCLUDE_PHOENIX_COMPONENTNODE_H
