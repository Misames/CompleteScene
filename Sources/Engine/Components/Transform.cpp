#include <iostream>

#include "Transform.hpp"

using namespace std;

Transform::~Transform()
{
    Release();
}

void Transform::Initialize()
{
    if (initialized)
        Release();

    position = vec3(0.0f);
    rotation = vec3(0.0f);
    scale = vec3(1.0f);

    initialized = true;
    enabled = true;
    cout << "Transform initialize" << endl;
}

void Transform::Release()
{
    initialized = false;
    enabled = false;
    cout << "Transform release" << endl;
}

void Transform::Update() {}
