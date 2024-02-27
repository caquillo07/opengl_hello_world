#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cassert>
#include "shader.h"
#include "VAO.h"
#include "EBO.h"

static void errorCallback(int error, const char *description) {
    fprintf(stderr, "GLFW Error (%d): %s\n", error, description);
}

static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main(int argc, char **argv) {
    glfwSetErrorCallback(errorCallback);
    if (!glfwInit()) {
        printf("failed to init glfw\n");
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // only run the core profile if running macos
#ifdef __APPLE__
    printf("running on macos\n");
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#elif __linux__
    printf("running on linux");
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLfloat vertices[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
        -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
        0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
        0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
    };

    // Indices for vertices order
    GLuint indices[] = {
        0, 3, 5, // Lower left triangle
        3, 2, 4, // Upper triangle
        5, 4, 1 // Lower right triangle
    };
    constexpr int width = 800;
    constexpr int height = 800;
    GLFWwindow *window = glfwCreateWindow(width, height, "Tutorial 01", nullptr, nullptr);
    if (!window) {
        printf("failed to create window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, keyCallback);

    glfwMakeContextCurrent(window);
    gladLoadGL();

    glViewport(0, 0, width, height);

    // because when ran from the IDE the current working directory is the .cmake-build-debug folder,
    // we need to do this BS... in a real project, we would need a macro or function
    // to handle the DEBUG case.
    Shader defaultShader(
        "../shaders/default.vert",
        "../shaders/default.frag"
    );

    // Create reference containers for the Vertex Array Object and the Vertex Buffer Object
    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));
    VAO1.LinkVBO(VBO1, 0);
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    while (!glfwWindowShouldClose(window)) {
        // Specify the color of the background
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT);
        // Tell OpenGL which Shader Program we want to use
        defaultShader.Activate();
        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();
        // Draw the triangle using the GL_TRIANGLES primitive
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);
        // Take care of all GLFW events
        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    defaultShader.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
