#pragma once

#include <glm/glm.hpp>

#include "IComponent.hpp"

using namespace glm;

class Transform : IComponent
{
public:
    vec3 position = vec3(0.f);
    vec3 rotation = vec3(0.f);
    vec3 scale = vec3(0.f);

    ~Transform() override;
    void Initialize() final;
    void Release() final;
    void Update() final;
};