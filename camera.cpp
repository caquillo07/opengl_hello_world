//
// Created by Hector Mejia on 2/27/24.
//

#include "camera.h"


#include  "shader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

Camera::Camera(const int width, const int height, const glm::vec3 position) {
    this->width = width;
    this->height = height;
    this->position = position;
}

void Camera::Matrix(
    const float fovDeg,
    const float nearPlane,
    const float farPlane,
    Shader& shader,
    const char* uniform
) const {
    const glm::mat4 view = glm::lookAt(position, position + orientation, up);
    const glm::mat4 projection = glm::perspective(glm::radians(fovDeg), (float)(width / height), nearPlane, farPlane);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::Inputs(GLFWwindow* window) {
    // Handles key inputs
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        this->position += speed * this->orientation;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        this->position += speed * -glm::normalize(glm::cross(this->orientation, this->up));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        this->position += speed * -this->orientation;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        this->position += speed * glm::normalize(glm::cross(this->orientation, this->up));
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        this->position += speed * this->up;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        this->position += speed * -this->up;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        speed = 0.4f;
    } else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
        speed = 0.1f;
    }


    // Handles mouse inputs
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        // Hides mouse cursor
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        // Prevents camera from jumping on the first click
        if (firstClick) {
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

        // Calculates upcoming vertical change in the this->orientation
        glm::vec3 newOrientation = glm::rotate(
            this->orientation,
            glm::radians(-rotX),
            glm::normalize(glm::cross(this->orientation, this->up))
        );

        // Decides whether or not the next vertical this->orientation is legal or not
        if (abs(glm::angle(newOrientation, this->up) - glm::radians(90.0f)) <= glm::radians(85.0f)) {
            this->orientation = newOrientation;
        }

        // Rotates the this->orientation left and right
        this->orientation = glm::rotate(this->orientation, glm::radians(-rotY), this->up);

        // Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
        glfwSetCursorPos(window, (width / 2), (height / 2));
    } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        // Unhides cursor since camera is not looking around anymore
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        // Makes sure the next time the camera looks around it doesn't jump
        firstClick = true;
    }
}
