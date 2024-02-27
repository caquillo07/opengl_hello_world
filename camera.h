//
// Created by Hector Mejia on 2/27/24.
//

#ifndef CAMERA_H
#define CAMERA_H


#include "shader.h"
#include <GLFW/glfw3.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>

struct GLFWwindow;

class Camera {
    public:
        glm::vec3 position{};
        glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

        int width;
        int height;

        float speed = 0.1;
        float sensitivity = 100.0f;

        Camera(int width, int height, glm::vec3 position);

        void Matrix(float fovDeg, float nearPlane, float farPlane, Shader& shader, const char* uniform) const;
        void Inputs(GLFWwindow* window);

    private:
        bool firstClick = true;
};

#endif //CAMERA_H
