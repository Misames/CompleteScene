#pragma once

#include "IEntity.hpp"

class IComponent
{
protected:
    uint64_t id;
    bool initialized, enabled = false;
    IEntity *entity;

public:
    virtual ~IComponent() = default;
    virtual void Initialize() = 0;
    virtual void Release() = 0;
    virtual void Update() = 0;
    IEntity *GetEntity() const;
};
