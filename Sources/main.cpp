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

GLShader shader;
Window mainWindow;
GLFWwindow *window = nullptr;
Camera camera = Camera(640, 480, glm::vec3(0.0f, 0.0f, 2.0f));

void LoadTexture()
{
    unsigned int textureId;
    unsigned char *data = new unsigned char[4]{255, 0, 255, 255};

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glActiveTexture(GL_TEXTURE0);

    delete[] data;
}

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

    shader.LoadVertexShader("Sources/Shaders/vertex.glsl");
    shader.LoadFragmentShader("Sources/Shaders/fragment.glsl");
    shader.Create();

    LoadTexture();

    return true;
}

void display()
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLuint program = shader.GetProgram();
    glUseProgram(program);

    float zNear = 0.1f, zFar = 1000.0f, fov = 45.0f;
    camera.Matrix(fov, zNear, zFar, &shader, "u_projection");

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

    window = mainWindow.GetHandle();
    while (!glfwWindowShouldClose(window))
    {
        camera.Inputs(window);
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}