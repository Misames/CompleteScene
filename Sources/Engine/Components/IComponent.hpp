#pragma once

#include <stdint.h>

class IComponent
{
protected:
    bool initialized = false;
    bool enabled = false;

public:
    virtual ~IComponent() = default;
    virtual void Initialize() = 0;
    virtual void Release() = 0;
    virtual void Update() = 0;
};
