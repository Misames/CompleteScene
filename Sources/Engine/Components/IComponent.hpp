#pragma once

#include <stdint.h>

class IComponent
{
protected:
    uint64_t id;
    bool initialized = false;

public:
    bool enabled = false;

    virtual ~IComponent() = default;
    virtual void Initialize() = 0;
    virtual void Release() = 0;
    virtual void Update() = 0;
    uint64_t GetId() const;
};
