#pragma once

#include <iostream>

#include <glm/glm.hpp>

#include "IComponent.hpp"

using namespace std;
using namespace glm;

class Transform : IComponent
{
public:
    vec3 position;
    vec3 rotation;
    vec3 scale;

    ~Transform() override;
    void Initialize() final;
    void Release() final;
    void Update() final;
};