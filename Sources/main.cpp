#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Engine/Renderer/Window.hpp"
#include "Engine/Core/Camera.hpp"
#include "Engine/Core/Texture.hpp"
#include "Tools/GLShader.hpp"

using namespace std;

GLfloat vertices[] = {-0.5f, -0.5f,
                      0.5f, -0.5f,
                      0.5f, 0.5f,
                      -0.5f, 0.5f};

GLuint indices[] = {0, 1, 2,
                    2, 3, 0};

GLShader defaultShader;
Window mainWindow;
Texture texture;
Camera camera = Camera(640, 480, glm::vec3(0.0f, 0.0f, 2.0f));

bool Initialize()
{
    try
    {
        mainWindow.Initialize(680, 460, "Complete Scene");
    }
    catch (const runtime_error &e)
    {
        cerr << e.what() << endl;
        return false;
    }

    defaultShader.LoadVertexShader("Sources/Shaders/vertex.glsl");
    defaultShader.LoadFragmentShader("Sources/Shaders/fragment.glsl");
    defaultShader.Create();
    texture.Initialize();

    return true;
}

void display(GLFWwindow *window)
{
    int widthWindow, heightWindow;
    glfwGetWindowSize(window, &widthWindow, &heightWindow);
    glViewport(0, 0, widthWindow, heightWindow);
    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLuint program = defaultShader.GetProgram();
    glUseProgram(program);

    float zNear = 0.1f, zFar = 1000.0f, fov = 45.0f;
    camera.Matrix(fov, zNear, zFar, &defaultShader, "u_projection");

    int positionLocation = glGetAttribLocation(program, "a_position");
    glEnableVertexAttribArray(positionLocation);

    GLuint VBO, EBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(positionLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void *)0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

int main()
{
    if (!Initialize())
        return -1;

    GLFWwindow *window = mainWindow.GetHandle();
    while (!glfwWindowShouldClose(window))
    {
        camera.Inputs(window);
        display(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}