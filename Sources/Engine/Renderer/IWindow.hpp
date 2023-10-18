#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct WindowInfo
{
    uint32_t width;
    uint32_t height;
    const char *title;
};

class IWindow
{
protected:
    bool initialized = false;
    GLFWwindow *glfwWindow = nullptr;

public:
    virtual ~IWindow() = default;
    virtual void Initialize(const WindowInfo &windowInfo) = 0;
    virtual void Release() = 0;
    GLFWwindow *GetHandle() const;
};