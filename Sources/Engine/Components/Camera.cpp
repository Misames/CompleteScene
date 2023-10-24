#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Camera.hpp"

Camera::Camera(vec3 position)
{
    this->position = position;
    cout << "Camera initialize" << endl;
}

Camera::~Camera()
{
    cout << "Camera release" << endl;
}

void Camera::Matrix(int width, int height, GLShader *shader, const char *uniform)
{
    // Initializes matrices since otherwise they will be the null matrix
    mat4 view = mat4(1.0f);
    mat4 projection = mat4(1.0f);

    // Makes camera look in the right direction from the right position
    view = lookAt(position, position + orientation, up);

    // Adds perspective to the scene
    projection = perspective(radians(fov), (float)width / height, near, far);

    // Exports the camera matrix to the Vertex Shader
    glUniformMatrix4fv(glGetUniformLocation(shader->GetProgram(), uniform), 1, GL_FALSE, value_ptr(projection * view));
}

void Camera::Inputs(int width, int height, GLFWwindow *window)
{
    // Handles key inputs
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

    // Handles mouse inputs
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        // Hides mouse cursor
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        // Prevents camera from jumping on the first click
        if (firstClick)
        {
            glfwSetCursorPos(window, (width / 2), (height / 2));
            firstClick = false;
        }

        // Stores the coordinates of the cursor
        double mouseX;
        double mouseY;

        // Fetches the coordinates of the cursor
        glfwGetCursorPos(window, &mouseX, &mouseY);

        // Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
        // and then "transforms" them into degrees
        float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
        float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

        // Calculates upcoming vertical change in the Orientation
        vec3 newOrientation = rotate(orientation, radians(-rotX), normalize(cross(orientation, up)));

        // Decides whether or not the next vertical Orientation is legal or not
        if (abs(angle(newOrientation, up) - radians(90.0f)) <= radians(85.0f))
            orientation = newOrientation;

        // Rotates the Orientation left and right
        orientation = rotate(orientation, radians(-rotY), up);

        // Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
        glfwSetCursorPos(window, (width / 2), (height / 2));
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        // Unhides cursor since camera is not looking around anymore
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        // Makes sure the next time the camera looks around it doesn't jump
        firstClick = true;
    }
}