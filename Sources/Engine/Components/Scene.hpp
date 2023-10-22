#pragma once

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Object.hpp"
#include "Camera.hpp"

using namespace std;

class Scene
{
private:
    uint8_t id;
    bool initialized = false;
    const char *name = "SampleScene";
    float zNear = 0.1f, zFar = 1000.0f, fov = 45.0f;
    Camera *camera;
    Object *obj;

public:
    ~Scene();
    void Initialize();
    void Release();
    void RenderScene(GLFWwindow *glfwWindow);
};