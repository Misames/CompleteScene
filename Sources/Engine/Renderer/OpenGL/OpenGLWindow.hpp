#pragma once

#include "../IWindow.hpp"

class OpenGLWindow : public IWindow
{
public:
    ~OpenGLWindow() override;
    void Initialize(const WindowInfo &windowInfo) final;
    void Release() final;
};