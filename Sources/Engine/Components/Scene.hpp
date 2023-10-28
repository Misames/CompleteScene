#pragma once

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Camera.hpp"
#include "Object.hpp"
#include "Skybox.hpp"

using namespace std;

class Scene
{
private:
    uint8_t id;
    bool initialized = false;
    vector<Object *> lstObj;
    Camera *camera = nullptr;
    Skybox *skybox = nullptr;

public:
    ~Scene();

    void Initialize();
    void Release();
    void RenderScene(GLFWwindow *glfwWindow);
};