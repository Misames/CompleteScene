#pragma once

#include <vector>
#include <stdint.h>

using namespace std;

class IComponent;

class IEntity
{
protected:
    bool initialized = false;
    uint64_t id;
    vector<IComponent *> components;

public:
    bool enabled = false;
    virtual ~IEntity() = default;
    virtual void Initialize() = 0;
    virtual void Release() = 0;
    vector<IComponent *> GetAllComponents() const;
    uint64_t GetId() const;
};