#pragma once

#include "Axes.hpp"
#include "Camera.hpp"
#include "Object.hpp"
#include "Skybox.hpp"

class Scene
{
private:
    bool initialized = false;
    Axes *axes = nullptr;
    Skybox *skybox = nullptr;
    Camera *camera = nullptr;
    vector<Object *> lstObj;

public:
    const char *name = "Main Scene";

    ~Scene();
    void Initialize();
    void Release();
    void RenderScene(GLFWwindow *glfwWindow);
};