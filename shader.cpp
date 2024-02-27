//
// Created by Hector Mejia on 2/26/24.
//

#include <cassert>

#include <fmt/core.h>

#include "shader.h"
#include "panic.h"

using string = std::string;

// Checks if the different Shaders have compiled properly
void compileErrors(unsigned int shader, const char *type) {
    // Stores status of compilation
    GLint hasCompiled;
    // Character array to store error message in
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            panic(fmt::format("SHADER_COMPILATION_ERROR for: {}\n{}", type, infoLog).c_str());
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            panic(fmt::format("SHADER_LINKING_ERROR for: {}\n{}", type, infoLog).c_str());
        }
    }
}

std::string readFile(const char *filename) {
    std::ifstream in(filename, std::ios::binary);
    panicIf(!in, fmt::format("Error opening {}: {}", filename, strerror(errno)).c_str());

    string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return contents;
}

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
    // Read vertexFile and fragmentFile and store the strings
    std::string vertexCode = readFile(vertexPath);
    std::string fragmentCode = readFile(fragmentPath);

    // Convert the shader source strings into character arrays
    const char *vertexSource = vertexCode.c_str();
    const char *fragmentSource = fragmentCode.c_str();

    const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);
    compileErrors(vertexShader, "VERTEX");

    const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);
    compileErrors(fragmentShader, "FRAGMENT");

    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertexShader);
    glAttachShader(this->ID, fragmentShader);

    // Wrap-up/Link all the shaders together into the Shader Program
    glLinkProgram(this->ID);
    compileErrors(this->ID, "PROGRAM");

    // delete the shaders as they are no longer needed, once they are attached
    // they are copied into the shader program/GPU memory.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate() const {
    // Tell OpenGL which Shader Program we want to use
    glUseProgram(this->ID);
}

void Shader::Delete() const {
    glDeleteProgram(this->ID);
}
