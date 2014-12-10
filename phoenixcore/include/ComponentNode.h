#pragma once
#ifndef INCLUDE_PHOENIX_COMPONENTNODE_H
#define INCLUDE_PHOENIX_COMPONENTNODE_H

typedef void*(*ComponentFinalizer)(void *component);

struct ComponentNode
{
    unsigned int identifier;
    void *component;
    ComponentFinalizer finalizer;
    ComponentNode *previous;
};

#endif //INCLUDE_PHOENIX_COMPONENTNODE_H