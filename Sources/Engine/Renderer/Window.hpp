#pragma once

#include "IWindow.hpp"

class Window : public IWindow
{
public:
    ~Window() override;
    void Initialize(unsigned int, unsigned int, const char *) final;
    void Release() final;
};