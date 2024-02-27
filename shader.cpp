//
// Created by Hector Mejia on 2/26/24.
//

#include <cassert>

#include <fmt/core.h>

#include "shader.h"
#include "panic.h"

using string = std::string;

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

    const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);

    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertexShader);
    glAttachShader(this->ID, fragmentShader);

    // Wrap-up/Link all the shaders together into the Shader Program
    glLinkProgram(this->ID);

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
