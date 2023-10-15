#include "IWindow.hpp"

GLFWwindow *IWindow::GetHandle() const
{
    return window;
}