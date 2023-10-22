#include "IComponent.hpp"

IEntity *IComponent::GetEntity() const
{
    return entity;
}
