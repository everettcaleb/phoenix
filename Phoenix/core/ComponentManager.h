#pragma once
#ifndef INCLUDE_PHOENIX_COMPONENTMANAGER_H
#define INCLUDE_PHOENIX_COMPONENTMANAGER_H

#include "CUID.h"
#include "ComponentNode.h"

class ComponentManager
{
private:
    ComponentNode *lastNode_;
    
    ComponentManager(const ComponentManager& other) {}

public:
    ComponentManager() : lastNode_(0) {}
    ~ComponentManager();

    void registerComponent(CUID identifier, void *component, ComponentFinalizer finalizer);

    inline void registerComponentOnHeap(CUID identifier, void *component) { registerComponent(identifier, component, DefaultHeapComponentFinalizer); }

    void *queryComponent(CUID identifier) const;
};

#endif //INCLUDE_PHOENIX_COMPONENTMANAGER_H
