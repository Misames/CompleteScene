#pragma once

#include <stdint.h>

class IComponent
{
protected:
    uint64_t id;
    bool enabled = false;
    bool initialized = false;

public:
    virtual ~IComponent() = default;
    virtual void Initialize() = 0;
    virtual void Release() = 0;
    virtual void Update() = 0;
};
