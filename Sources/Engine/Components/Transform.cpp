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

    initialized = true;
    enabled = true;
    cout << "Transform initialize" << endl;
}

void Transform::Release()
{
    if (initialized)
    {
        initialized = false;
        enabled = false;
        cout << "Transform release" << endl;
    }
}

void Transform::Update() {}
