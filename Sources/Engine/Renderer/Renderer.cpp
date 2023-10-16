#include <iostream>
#include "Renderer.hpp"

using namespace std;

Renderer::~Renderer()
{
    Release();
}

void Renderer::Initialize(const RendererInfo &renderInfo)
{
    if (initialized)
        Release();

    m_window.Initialize(*renderInfo.windowInfo);
    window = &m_window;
    initialized = true;
    cout << "Renderer initialize" << endl;
}

void Renderer::Release()
{
    if (initialized)
    {
        m_window.Release();
        window = nullptr;
        initialized = false;
        cout << "Renderer release" << endl;
    }
}
