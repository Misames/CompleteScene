#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Engine.hpp"
#include "Renderer/RasterizationEngine.hpp"

using namespace std;

Engine::~Engine()
{
    Release();
}

void Engine::Initialize(const EngineInfo &info)
{
    if (initialize)
        Release();

    switch (info.renderingEngineInfo->renderingEngineType)
    {
    case RASTERIZATION:
        renderingEngine = new RasterizationEngine();
        break;
    case RAY_TRACING_CPU:
        throw runtime_error("Ray Tracing CPU not implemented");
        break;
    case RAY_TRACING_GPU:
        throw runtime_error("Ray Tracing GPU not implemented");
        break;
    }

    if (!renderingEngine)
        throw bad_alloc();

    renderingEngine->Initialize(*info.renderingEngineInfo);
    initialize = true;
    cout << "Engine initialize" << endl;
}

void Engine::Release()
{
    if (initialize)
    {
        if (renderingEngine)
        {
            renderingEngine->Release();
            delete renderingEngine;
            renderingEngine = nullptr;
        }

        initialize = false;
        cout << "Engine release" << endl;
    }
}

void Engine::Run()
{
    if (!initialize)
        throw runtime_error("Engine not initialize");

    GLFWwindow *glfwWindow = renderingEngine->GetRenderer()->GetWindow()->GetHandle();

    double lag = 0.0;
    double previous = glfwGetTime();
    double SECONDS_PER_UPDATE = 1.0 / 60.0;

    while (!glfwWindowShouldClose(glfwWindow))
    {
        double currentTime = glfwGetTime();
        double elapsedTime = currentTime - previous;
        previous = currentTime;
        lag += elapsedTime;

        glfwPollEvents();

        while (lag >= SECONDS_PER_UPDATE)
        {
            // Game Logic
            lag -= SECONDS_PER_UPDATE;
        }

        renderingEngine->Render(static_cast<float>(lag / SECONDS_PER_UPDATE));
    }
}
