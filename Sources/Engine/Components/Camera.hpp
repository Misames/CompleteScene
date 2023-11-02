#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GLShader.hpp"
#include "Transform.hpp"

using namespace std;
using namespace glm;

class Camera
{
private:
    bool firstClick = true;
    float speed = 0.1f;
    float sensitivity = 100.0f;
    float near = 0.1f;
    float far = 1000.0f;
    float fov = 45.0f;

    vec3 position;
    vec3 orientation = vec3(0.0f, 0.0f, -1.0f);
    vec3 up = vec3(0.0f, 1.0f, 0.0f);
    Transform *transform = nullptr;

public:
    Camera(vec3 position);
    ~Camera();
    void Matrix(int width, int height, GLuint program);
    void Inputs(int width, int height, GLFWwindow *window);
};