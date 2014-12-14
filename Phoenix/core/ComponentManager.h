#pragma once
#ifndef INCLUDE_PHOENIX_COMPONENTMANAGER_H
#define INCLUDE_PHOENIX_COMPONENTMANAGER_H

#include "CUID.h"
#include "ComponentNode.h"

class ComponentManager
{
private:
    ComponentNode *lastNode_;

    ComponentManager() : lastNode_(0) {}
    ComponentManager(const ComponentManager& other) {}

public:
    ~ComponentManager();

    void registerComponent(CUID identifier, void *component, ComponentFinalizer finalizer);

    inline void registerComponentOnHeap(CUID identifier, void *component) { registerComponent(identifier, component, DefaultHeapComponentFinalizer); }

    void *queryComponent(CUID identifier);

    inline static ComponentManager *create() { return new ComponentManager(); }
};

#endif //INCLUDE_PHOENIX_COMPONENTMANAGER_H