#include "ComponentManager.h"

//========================================================================================================

ComponentManager::~ComponentManager() 
{
    ComponentNode *temp;

    while (lastNode_) 
    {
        temp = lastNode_;
        if (lastNode_->finalizer) {
            lastNode_->finalizer(lastNode_->component);
        }
        lastNode_ = lastNode_->previous;
        delete temp;
    }
}

//========================================================================================================

void ComponentManager::registerComponent(CUID identifier, void *component, ComponentFinalizer finalizer)
{
    ComponentNode *node = new ComponentNode;
    node->identifier = identifier;
    node->component = component;
    node->finalizer = finalizer;
    node->previous = lastNode_;
    lastNode_ = node;
}

//========================================================================================================

void *ComponentManager::queryComponent(CUID identifier) const
{
    ComponentNode *temp = lastNode_;

    while (temp)
    {
        if (temp->identifier == identifier)
        {
            return temp->component;
        }
        temp = temp->previous;
    }

    return 0;
}

//========================================================================================================

void DefaultHeapComponentFinalizer(void *component)
{
    delete component;
}
