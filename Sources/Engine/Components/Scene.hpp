#pragma once
#include <vector>
#include "Object.hpp"

using namespace std;

class Scene
{
private:
    vector<Object> objScene;

public:
    Scene() {}
    ~Scene() {}
};