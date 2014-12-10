#pragma once
#ifndef INCLUDE_PHOENIX_COMPONENTMANAGER_H
#define INCLUDE_PHOENIX_COMPONENTMANAGER_H

#include "ComponentNode.h"

class ComponentManager
{
private:
    ComponentNode *lastNode_;

    ComponentManager() : lastNode_(0) {}
    ComponentManager(const ComponentManager& other) {}

public:
    ~ComponentManager();

    void registerComponent(unsigned int identifier, void *component, ComponentFinalizer finalizer);
    void *queryComponent(unsigned int identifier);

    inline static ComponentManager *create() { return new ComponentManager(); }
};

#endif //INCLUDE_PHOENIX_COMPONENTMANAGER_H