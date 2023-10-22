#include "IEntity.hpp"

vector<IComponent *> IEntity::GetAllComponents() const
{
    return components;
}

uint64_t IEntity::GetId() const
{
    return id;
}
