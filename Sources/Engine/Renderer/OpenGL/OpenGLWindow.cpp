#include "OpenGLWindow.hpp"

void errorCallback(int error, const char *description)
{
    cout << "Error GFLW " << error << " : " << description << endl;
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

OpenGLWindow::~OpenGLWindow()
{
    Release();
}

void OpenGLWindow::Initialize(const WindowInfo &windowInfo)
{
    if (initialized)
        Release();

    glfwSetErrorCallback(errorCallback);

    if (!glfwInit())
        throw runtime_error("Fail to initialize GLFW");

    glfwWindow = glfwCreateWindow(windowInfo.width,
                                  windowInfo.height,
                                  windowInfo.title,
                                  nullptr, nullptr);
    if (!glfwWindow)
    {
        glfwTerminate();
        throw runtime_error("Fail to create window");
    }

    glfwMakeContextCurrent(glfwWindow);
    glfwSetKeyCallback(glfwWindow, keyCallback);

    GLenum error = glewInit();
    if (error != GLEW_OK)
        cout << "GLEW initialization failled!" << endl;

    initialized = true;
    cout << "Window initialize" << endl;
}

void OpenGLWindow::Release()
{
    if (initialized)
    {
        glfwTerminate();
        glfwWindow = nullptr;
        initialized = false;
        cout << "Window release" << endl;
    }
}
