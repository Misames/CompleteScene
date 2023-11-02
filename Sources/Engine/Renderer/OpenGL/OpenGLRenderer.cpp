#include <iostream>

#include "OpenGLRenderer.hpp"

using namespace std;

OpenGLRenderer::~OpenGLRenderer()
{
    Release();
}

void OpenGLRenderer::Initialize(const RendererInfo &renderInfo)
{
    if (initialized)
        Release();

    openglWindow.Initialize(*renderInfo.windowInfo);
    window = &openglWindow;

    initialized = true;
    cout << "Renderer initialize" << endl;
}

void OpenGLRenderer::Release()
{
    if (initialized)
    {
        openglWindow.Release();
        window = nullptr;

        initialized = false;
        cout << "Renderer release" << endl;
    }
}
