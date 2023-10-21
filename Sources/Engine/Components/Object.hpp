#pragma once

#include "Mesh.hpp"
#include "Transform.hpp"

class Object
{
private:
    Mesh mesh;
    Transform transform;

public:
    Object() {}
    ~Object() {}
};