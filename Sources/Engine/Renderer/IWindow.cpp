#include "IWindow.hpp"

GLFWwindow *IWindow::GetHandle() const
{
    return glfwWindow;
}