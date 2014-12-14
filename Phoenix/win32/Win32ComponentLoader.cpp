#ifdef WIN32

#include "../core/IComponentLoader.h"
#include <Windows.h>

//========================================================================================================

class Win32ComponentLoader : public IComponentLoader
{
public:
    Win32ComponentLoader() {}
    ~Win32ComponentLoader() {}

    bool LoadByFactoryName(const char *factoryName, ComponentNode *output) const;
    bool LoadByFactoryNameFromLibrary(const char *factoryName, const char *libraryName, ComponentNode *output) const;
};

//========================================================================================================

bool Win32ComponentLoader::LoadByFactoryName(const char *factoryName, ComponentNode *output) const
{
    ComponentFactoryFunction function = (ComponentFactoryFunction)GetProcAddress(GetModuleHandle(NULL), factoryName);
    if (function)
    {
        function(output);
        return true;
    }
    return false;
}

//========================================================================================================

bool Win32ComponentLoader::LoadByFactoryNameFromLibrary(const char *factoryName, const char *libraryName, ComponentNode *output) const
{
    HMODULE handle = GetModuleHandleA(libraryName);
    if (handle == NULL) 
    {
        handle = LoadLibraryA(libraryName);
    }
    if (handle == NULL)
    {
        return false;
    }

    ComponentFactoryFunction function = (ComponentFactoryFunction)GetProcAddress(handle, factoryName);
    if (function)
    {
        function(output);
        return true;
    }
    return false;
}

//========================================================================================================

IComponentLoader *CreateComponentLoader() 
{
    return new Win32ComponentLoader;
}

#endif