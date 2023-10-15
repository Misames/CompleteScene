#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class IWindow
{
protected:
    const char *name;
    unsigned int height;
    unsigned int width;
    GLFWwindow *window = nullptr;

public:
    virtual ~IWindow() = default;
    virtual void Initialize(unsigned int width, unsigned int height, const char *name) = 0;
    virtual void Release() = 0;
    GLFWwindow *GetHandle() const;
};