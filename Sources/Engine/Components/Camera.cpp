#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Camera.hpp"

Camera::Camera(vec3 position)
{
    this->position = position;
    transform = new Transform();
    transform->Initialize();
    cout << "Camera initialize" << endl;
}

Camera::~Camera()
{
    if (transform)
    {
        transform->Release();
        delete transform;
        transform = nullptr;
    }

    cout << "Camera release" << endl;
}

void Camera::Matrix(int width, int height, GLuint program)
{
    mat4 view = mat4(1.0f);
    mat4 projection = mat4(1.0f);

    view = lookAt(position, position + orientation, up);
    projection = perspective(radians(fov), (float)width / height, near, far);

    glUniformMatrix4fv(glGetUniformLocation(program, "uProjection"), 1, GL_FALSE, value_ptr(projection * view));
}

void Camera::Inputs(int width, int height, GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += speed * orientation;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position += speed * -normalize(cross(orientation, up));

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position += speed * -orientation;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += speed * normalize(cross(orientation, up));

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        position += speed * up;

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        position += speed * -up;

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        speed = 0.4f;
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
        speed = 0.1f;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if (firstClick)
        {
            glfwSetCursorPos(window, (width / 2), (height / 2));
            firstClick = false;
        }

        double mouseX;
        double mouseY;

        glfwGetCursorPos(window, &mouseX, &mouseY);

        float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
        float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

        vec3 newOrientation = rotate(orientation, radians(-rotX), normalize(cross(orientation, up)));

        if (abs(angle(newOrientation, up) - radians(90.0f)) <= radians(85.0f))
            orientation = newOrientation;

        orientation = rotate(orientation, radians(-rotY), up);

        glfwSetCursorPos(window, (width / 2), (height / 2));
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }
}