#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Engine/Core/Camera.hpp"
#include "Tools/GLShader.hpp"

using namespace std;

GLfloat vertices[] = {-0.5f, -0.5f,
                      0.5f, -0.5f,
                      0.5f, 0.5f,
                      -0.5f, 0.5f};

GLuint indices[] = {0, 1,
                    2, 2,
                    3, 0};

GLShader *defaultShader = new GLShader();
Camera *camera = new Camera(640, 480, glm::vec3(0.0f, 0.0f, 2.0f));

void display(GLFWwindow *window)
{
    int widthWindow, heightWindow;
    glfwGetWindowSize(window, &widthWindow, &heightWindow);
    glViewport(0, 0, widthWindow, heightWindow);
    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLuint program = defaultShader->GetProgram();
    glUseProgram(program);

    float znear = 0.1f, zfar = 1000.0f, fov = 45.0f;
    camera->Matrix(fov, znear, zfar, defaultShader, "projection");

    int attribLocation = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(attribLocation);

    GLuint VBO, EBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(attribLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(attribLocation);
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

    window = glfwCreateWindow(640, 480, "Complete Scene", nullptr, nullptr);
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

#ifdef _DEBUG
    defaultShader->LoadVertexShader("Sources/Shaders/vertex.glsl");
    defaultShader->LoadFragmentShader("Sources/Shaders/fragment.glsl");
    defaultShader->Create();
#else
    defaultShader->LoadVertexShader("vertex.glsl");
    defaultShader->LoadFragmentShader("fragment.glsl");
    defaultShader->Create();
#endif

    while (!glfwWindowShouldClose(window))
    {
        camera->Inputs(window);
        display(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}