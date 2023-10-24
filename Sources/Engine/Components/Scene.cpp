#include "Scene.hpp"

Scene::~Scene()
{
    Release();
}

void Scene::Initialize()
{
    if (initialized)
        Release();

    camera = new Camera(vec3(0.0f, 0.0f, 2.0f));
    if (!camera)
        throw bad_alloc();

    Object *obj = new Object();
    if (!obj)
        throw bad_alloc();

    obj->Initialize();
    obj->GetMesh()->LoadMesh("Sources/Assets/Mesh/lightning_obj.obj");
    uint8_t pink[4] = {255, 0, 255, 255};
    obj->GetTexture()->Load(pink);
    obj->enabled = true;
    lstObj.push_back(obj);

    Object *obj2 = new Object();
    if (!obj2)
        throw bad_alloc();

    obj2->Initialize();
    obj2->GetMesh()->LoadMesh("Sources/Assets/Mesh/cube.obj");
    obj2->enabled = true;
    lstObj.push_back(obj2);

    initialized = true;
    cout << "Scene initialize" << endl;
}

void Scene::Release()
{
    if (initialized)
    {
        for (Object *currentObject : lstObj)
        {
            currentObject->Release();
            delete currentObject;
            currentObject = nullptr;
        }

        delete camera;
        camera = nullptr;

        initialized = false;
        cout << "Scene release" << endl;
    }
}

void Scene::RenderScene(GLFWwindow *glfwWindow)
{
    int width, height;
    glfwGetWindowSize(glfwWindow, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    camera->Inputs(width, height, glfwWindow);
    for (Object *currentObject : lstObj)
    {
        camera->Matrix(width, height, currentObject->GetShader(), "u_projection");
        currentObject->Render();
    }

    glfwSwapBuffers(glfwWindow);
}
