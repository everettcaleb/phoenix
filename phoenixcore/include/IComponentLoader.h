#pragma once
#ifndef INCLUDE_PHOENIX_ICOMPONENTLOADER_H
#define INCLUDE_PHOENIX_ICOMPONENTLOADER_H

#include "ComponentNode.h"

typedef void(*ComponentFactoryFunction)(ComponentNode *output);

class IComponentLoader 
{
private: 
    IComponentLoader(const IComponentLoader& other) {}

protected:
    IComponentLoader() {}

public:
    virtual ~IComponentLoader() {}

    virtual bool LoadByFactoryName(const char *factoryName, ComponentNode *output) const = 0;
    virtual bool LoadByFactoryNameFromLibrary(const char *factoryName, const char *libraryName, ComponentNode *output) const = 0;
};

extern IComponentLoader *CreateComponentLoader();

#endif //INCLUDE_PHOENIX_ICOMPONENTLOADER_H