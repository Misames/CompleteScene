#pragma once

#include <iostream>
#include "OpenGLWindow.hpp"
#include "../IRenderer.hpp"

using namespace std;

class OpenGLRenderer : public IRenderer
{
private:
    OpenGLWindow openglWindow;

public:
    ~OpenGLRenderer() override;
    void Initialize(const RendererInfo &renderInfo) final;
    void Release() final;
};