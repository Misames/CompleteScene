#pragma once

#include "IWindow.hpp"

class Window : public IWindow
{
public:
    Window();
    ~Window() override;
    void Initialize(unsigned int width, unsigned int height, const char *name) final;
    void Release() final;
};