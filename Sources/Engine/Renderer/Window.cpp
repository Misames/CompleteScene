#include <iostream>
#include "Window.hpp"

using namespace std;

static void errorCallback(int error, const char *description)
{
    cout << "Error GFLW " << error << " : " << description << endl;
}

static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

Window::~Window()
{
    Release();
}

void Window::Initialize(unsigned int width, unsigned int height, const char *name)
{
    glfwSetErrorCallback(errorCallback);

    if (!glfwInit())
        throw runtime_error("Fail to initialize GLFW");

    window = glfwCreateWindow(width, height, name, nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        throw runtime_error("Fail create window");
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);

    GLenum error = glewInit();
    if (error != GLEW_OK)
        cout << "erreur d'initialisation de GLEW!" << endl;
}

void Window::Release()
{
    glfwTerminate();
    window = nullptr;
}
