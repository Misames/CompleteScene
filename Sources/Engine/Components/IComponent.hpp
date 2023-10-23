#pragma once

#include "IEntity.hpp"

class IComponent
{
protected:
    bool initialized, enabled = false;
    uint64_t id;
    IEntity *entity;

public:
    virtual ~IComponent() = default;
    virtual void Initialize() = 0;
    virtual void Release() = 0;
    virtual void Update() = 0;
    IEntity *GetEntity() const;
};
