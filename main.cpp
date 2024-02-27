#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include<glm/glm.hpp>

#include "shader.h"
#include "VAO.h"
#include "EBO.h"
#include "panic.h"
#include "texture.h"
#include "camera.h"

GLfloat vertices[] = {
    -0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
    -0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f,
    0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
    0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f,
    0.0f, 0.8f, 0.0f, 0.92f, 0.86f, 0.76f, 2.5f, 5.0f
};

// Indices for vertices order
GLuint indices[] = {
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
};


static void errorCallback(int error, const char* description) {
    fprintf(stderr, "GLFW Error (%d): %s\n", error, description);
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main(int argc, char** argv) {
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

    constexpr int width = 800;
    constexpr int height = 800;
    GLFWwindow* window = glfwCreateWindow(width, height, "Tutorial 01", nullptr, nullptr);
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
    const VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    const EBO EBO1(indices, sizeof(indices));
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();


    // textures
    Texture brickTex("../textures/brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    brickTex.texUnit(defaultShader, "tex0", 0);

    GLint tex0Uni = glGetUniformLocation(defaultShader.ID, "tex0");
    defaultShader.Activate();
    glUniform1i(tex0Uni, 0);

    // enables depth buffers
    glEnable(GL_DEPTH_TEST);

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    while (!glfwWindowShouldClose(window)) {
        // Specify the color of the background
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Tell OpenGL which Shader Program we want to use
        defaultShader.Activate();

        camera.Inputs(window);
        camera.Matrix(45.f, 0.1f, 100.f, defaultShader, "camMatrix");


        brickTex.Bind();
        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();
        // Draw the triangle using the GL_TRIANGLES primitive
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);
        // Take care of all GLFW events
        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    brickTex.Delete();
    defaultShader.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
