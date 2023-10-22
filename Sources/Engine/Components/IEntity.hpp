#pragma once

#include <vector>
#include <stdint.h>

using namespace std;

class IComponent;

class IEntity
{
protected:
    uint64_t id;
    bool initialized, enabled = false;
    vector<IComponent *> components;

public:
    virtual ~IEntity() = default;
    virtual void Initialize() = 0;
    virtual void Release() = 0;
    vector<IComponent *> GetAllComponents() const;
    uint64_t GetId() const;
};