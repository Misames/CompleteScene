#pragma once

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Skybox.hpp"
#include "Camera.hpp"
#include "Object.hpp"

using namespace std;

class Scene
{
private:
    uint8_t id;
    bool initialized = false;
    Skybox *skybox = nullptr;
    Camera *camera = nullptr;
    vector<Object *> lstObj;

public:
    ~Scene();
    void Initialize();
    void Release();
    void RenderScene(GLFWwindow *glfwWindow);
};