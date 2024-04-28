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

    skybox = new Skybox();
    if (!skybox)
        throw bad_alloc();
    skybox->Initialize();

    axes = new Axes();
    if (!axes)
        throw bad_alloc();
    axes->Initialize();

    camera = new Camera(vec3(0.0f, 0.0f, 2.0f));
    if (!camera)
        throw bad_alloc();

    Object *lightning = new Object();
    if (!lightning)
        throw bad_alloc();
    lightning->Initialize();
    lightning->GetMesh()->LoadMesh("Sources/Assets/Mesh/lightning_obj.obj");
    lightning->GetTexture()->LoadImage("Sources/Assets/Textures/brick.png");
    lstObj.push_back(lightning);

    Object *cube = new Object();
    if (!cube)
        throw bad_alloc();
    cube->Initialize();
    cube->GetMesh()->LoadMesh("Sources/Assets/Mesh/cube.obj");
    lstObj.push_back(cube);

    initialized = true;
    cout << "Scene initialize" << endl;
}

void Scene::Release()
{
    if (initialized)
    {
        if (axes)
        {
            axes->Release();
            delete axes;
            axes = nullptr;
        }

        if (skybox)
        {
            skybox->Release();
            delete skybox;
            skybox = nullptr;
        }

        if (camera)
        {
            delete camera;
            camera = nullptr;
        }

        for (Object *currentObject : lstObj)
        {
            currentObject->Release();
            delete currentObject;
            currentObject = nullptr;
        }

        initialized = false;
        cout << "Scene release" << endl;
    }
}

void Scene::RenderScene(GLFWwindow *glfwWindow)
{
    int widthWindow, heightWindow;
    glfwGetWindowSize(glfwWindow, &widthWindow, &heightWindow);
    glViewport(0, 0, widthWindow, heightWindow);

    camera->Inputs(widthWindow, heightWindow, glfwWindow);

    for (Object *currentObject : lstObj)
    {
        camera->Matrix(widthWindow, heightWindow, currentObject->GetShader()->GetProgram());
        currentObject->Render();
    }

    camera->Matrix(widthWindow, heightWindow, axes->GetShader()->GetProgram());
    axes->Render(widthWindow, heightWindow);
}
