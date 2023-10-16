#pragma once

#include "IWindow.hpp"

class Window : public IWindow
{
public:
    ~Window() override;
    void Initialize(const WindowInfo &windowInfo) final;
    void Release() final;
};