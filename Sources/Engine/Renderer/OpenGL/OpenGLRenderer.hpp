#pragma once

#include "../IRenderer.hpp"
#include "OpenGLWindow.hpp"

class OpenGLRenderer : public IRenderer
{
private:
    OpenGLWindow openglWindow;

public:
    ~OpenGLRenderer() override;
    void Initialize(const RendererInfo &renderInfo) final;
    void Release() final;
};