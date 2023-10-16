#pragma once

#include "IRenderer.hpp"
#include "Window.hpp"

class Renderer : public IRenderer
{
private:
    Window m_window;

public:
    ~Renderer() override;
    void Initialize(const RendererInfo &renderInfo) final;
    void Release() final;
};