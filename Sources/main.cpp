#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

void Initialize()
{
    GLenum error = glewInit();
    if (error != GLEW_OK)
        cout << "erreur d'initialisation de GLEW!" << endl;

    // Logs
    cout << "Version : " << glGetString(GL_VERSION) << endl;
    cout << "Vendor : " << glGetString(GL_VENDOR) << endl;
    cout << "Renderer : " << glGetString(GL_RENDERER) << endl;
}

void Display(GLFWwindow *window)
{
    int widthWindow, heightWindow;
    glfwGetWindowSize(window, &widthWindow, &heightWindow);
    glViewport(0, 0, widthWindow, heightWindow);

    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
}

static void error_callback(int error, const char *description)
{
    cout << "Error GFLW " << error << " : " << description << endl;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
    GLFWwindow *window;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Project name", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    Initialize();

    while (!glfwWindowShouldClose(window))
    {
        Display(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}