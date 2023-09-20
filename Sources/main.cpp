#include <cstddef>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

float vertices[] = {-0.5f, -0.5f,
                    0.5f, -0.5f,
                    0.5f, 0.5f,
                    -0.5f, 0.5f};

unsigned int indices[] = {0, 1, 2,
                          2, 3, 0};

void display(GLFWwindow *window)
{
    int widthWindow, heightWindow;
    glfwGetWindowSize(window, &widthWindow, &heightWindow);
    glViewport(0, 0, widthWindow, heightWindow);
    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLuint VBO, EBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

static void errorCallback(int error, const char *description)
{
    cout << "Error GFLW " << error << " : " << description << endl;
}

static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
    GLFWwindow *window;

    glfwSetErrorCallback(errorCallback);

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Project name", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);

    GLenum error = glewInit();
    if (error != GLEW_OK)
        cout << "erreur d'initialisation de GLEW!" << endl;

    while (!glfwWindowShouldClose(window))
    {
        display(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}