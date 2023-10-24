#pragma once

#include <iostream>
#include "../IWindow.hpp"

using namespace std;

class OpenGLWindow : public IWindow
{
public:
    ~OpenGLWindow() override;
    void Initialize(const WindowInfo &windowInfo) final;
    void Release() final;
};