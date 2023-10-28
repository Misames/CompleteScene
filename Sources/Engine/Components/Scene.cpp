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

    camera = new Camera(vec3(0.0f, 0.0f, 2.0f));
    if (!camera)
        throw bad_alloc();

    Object *lightning = new Object();
    if (!lightning)
        throw bad_alloc();
    lightning->Initialize();
    lightning->GetMesh()->LoadMesh("Sources/Assets/Mesh/lightning_obj.obj");
    uint8_t pink[4] = {255, 0, 255, 255};
    lightning->GetTexture()->Load(pink);
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
        skybox->Release();
        delete skybox;
        skybox = nullptr;

        delete camera;
        camera = nullptr;

        for (Object *currentObject : lstObj)
        {
            currentObject->Release();
            delete currentObject;
            currentObject = nullptr;
        }

        glUseProgram(0);
        glBindVertexArray(0);

        initialized = false;
        cout << "Scene release" << endl;
    }
}

void Scene::RenderScene(GLFWwindow *glfwWindow)
{
    int widthWindow, heightWindow;
    glfwGetWindowSize(glfwWindow, &widthWindow, &heightWindow);
    glViewport(0, 0, widthWindow, heightWindow);
    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    camera->Inputs(widthWindow, heightWindow, glfwWindow);

    for (Object *currentObject : lstObj)
    {
        camera->Matrix(widthWindow, heightWindow, currentObject->GetShader()->GetProgram(), "u_projection");
        currentObject->Render();
    }

    glfwSwapBuffers(glfwWindow);
}
