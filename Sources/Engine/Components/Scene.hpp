#pragma once

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Camera.hpp"
#include "Object.hpp"

using namespace std;

class Scene
{
private:
    uint8_t id;
    bool initialized = false;
    const char *name = "SampleScene";
    vector<Object *> lstObj;
    Camera *camera = nullptr;

public:
    ~Scene();

    void Initialize();
    void Release();
    void RenderScene(GLFWwindow *glfwWindow);
};