#include <iostream>
#include "Scene.hpp"

Scene::~Scene()
{
    Release();
}

void Scene::Initialize()
{
    if (initialized)
        Release();

    camera = new Camera(640, 480, vec3(0.0f, 0.0f, 2.0f));
    if (!camera)
        throw bad_alloc();

    obj = new Object();
    if (!obj)
        throw bad_alloc();

    obj->Initialize();

    initialized = true;
    cout << "Scene initialize" << endl;
}

void Scene::Release()
{
    if (initialized)
    {
        obj->Release();
        delete obj, camera;
        obj, camera = nullptr;

        initialized = false;
        cout << "Scene release" << endl;
    }
}

void Scene::RenderScene(GLFWwindow *glfwWindow)
{
    camera->Inputs(glfwWindow);

    int width, height;
    glfwGetWindowSize(glfwWindow, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    camera->Matrix(fov, zNear, zFar, obj->GetShader(), "u_projection");
    obj->Render();

    glfwSwapBuffers(glfwWindow);
}
