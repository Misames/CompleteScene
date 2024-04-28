#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "OpenGL/OpenGLRenderer.hpp"

#include "RasterizationEngine.hpp"

RasterizationEngine::~RasterizationEngine()
{
    Release();
}

void RasterizationEngine::Initialize(const RenderingEngineInfo &renderingEngineInfo)
{
    if (initialized)
        Release();

    switch (renderingEngineInfo.rendererInfo->rendererType)
    {
    case OPENGL:
        renderer = new OpenGLRenderer();
        break;
    case VULKAN:
        throw runtime_error("Vulkan renderer not implemented");
        break;
    case DIRECTX:
        throw runtime_error("DirectX renderer not implemented");
        break;
    }

    if (!renderer)
        throw bad_alloc();
    renderer->Initialize(*renderingEngineInfo.rendererInfo);

    scene = new Scene();
    if (!scene)
        throw bad_alloc();
    scene->Initialize();

    glfwSetWindowTitle(renderer->GetWindow()->GetHandle(), scene->name);

    initialized = true;
    cout << "RasterizationEngine initialize" << endl;
}

void RasterizationEngine::Release()
{
    if (initialized)
    {
        if (renderer)
        {
            renderer->Release();
            delete renderer;
            renderer = nullptr;
        }

        if (scene)
        {
            scene->Release();
            delete scene;
            scene = nullptr;
        }

        initialized = false;
        cout << "RasterizationEngine release" << endl;
    }
}

void RasterizationEngine::Render(float lag)
{
    GLFWwindow *glfwWindow = renderer->GetWindow()->GetHandle();
    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    scene->RenderScene(glfwWindow);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Window title");
    ImGui::Text("Some text");
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(glfwWindow);
}