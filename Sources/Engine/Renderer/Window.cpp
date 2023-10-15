#include <iostream>

#include "Window.hpp"

using namespace std;

void errorCallback(int error, const char *description)
{
    cout << "Error GFLW " << error << " : " << description << endl;
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

Window::Window()
{
    cout << "Init Window" << endl;
}

Window::~Window()
{
    Release();
    cout << "Destroy Window" << endl;
}

void Window::Initialize(unsigned int width, unsigned int heught, const char *name)
{
    glfwSetErrorCallback(errorCallback);

    if (!glfwInit())
        throw runtime_error("Fail to initialize GLFW");

    window = glfwCreateWindow(width, heught, name, nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        throw runtime_error("Fail to create window");
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);

    GLenum error = glewInit();
    if (error != GLEW_OK)
        cout << "GLEW initialization failled!" << endl;
}

void Window::Release()
{
    glfwTerminate();
    window = nullptr;
}
