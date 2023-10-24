#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "../../Tools/GLShader.hpp"

using namespace std;
using namespace glm;

class Camera
{
private:
    // Stores the main vectors of the camera
    vec3 position;
    vec3 orientation = vec3(0.0f, 0.0f, -1.0f);
    vec3 up = vec3(0.0f, 1.0f, 0.0f);

    // Prevents the camera from jumping around when first clicking left click
    bool firstClick = true;

public:
    // Adjust the speed of the camera and it's sensitivity when looking around
    float speed = 0.1f;
    float sensitivity = 100.0f;

    float near = 0.1f;
    float far = 1000.0f;
    float fov = 45.0f;

    // Camera constructor to set up initial values
    Camera(vec3 position);
    ~Camera();

    // Updates and exports the camera matrix to the Vertex Shader
    void Matrix(int width, int height, GLShader *shader, const char *uniform);

    // Handles camera inputs
    void Inputs(int width, int height, GLFWwindow *window);
};