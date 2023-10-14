#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class IWindow
{
protected:
    unsigned int width;
    unsigned int height;
    const char *name;
    GLFWwindow *window = nullptr;

public:
    virtual ~IWindow() = default;
    virtual void Initialize(unsigned int, unsigned int, const char *) = 0;
    virtual void Release() = 0;
    GLFWwindow *GetHandle();
};