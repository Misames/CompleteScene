#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Engine/Renderer/Window.hpp"
#include "Engine/Core/Camera.hpp"
#include "Tools/GLShader.hpp"

using namespace std;

GLfloat vertices[] = {-0.5f, -0.5f,
                      0.5f, -0.5f,
                      0.5f, 0.5f,
                      -0.5f, 0.5f};

GLuint indices[] = {0, 1, 2,
                    2, 3, 0};

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

int main()
{
    Window *mainWindow = new Window();

    try
    {
        mainWindow->Initialize(680, 460, "Complete Scene");
    }
    catch (const runtime_error &e)
    {
        cerr << e.what() << '\n';
        return -1;
    }

    GLFWwindow *window = mainWindow->GetHandle();

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

    return 0;
}