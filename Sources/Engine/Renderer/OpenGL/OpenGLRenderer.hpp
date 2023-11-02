#pragma once

#include "OpenGLWindow.hpp"
#include "../IRenderer.hpp"

class OpenGLRenderer : public IRenderer
{
private:
    OpenGLWindow openglWindow;

public:
    ~OpenGLRenderer() override;
    void Initialize(const RendererInfo &renderInfo) final;
    void Release() final;
};