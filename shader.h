//
// Created by Hector Mejia on 2/26/24.
//

#ifndef OPENGL_HELLO_WORLD_SHADER_H
#define OPENGL_HELLO_WORLD_SHADER_H

#include <fstream>
#include <string>
#include <glad/glad.h>

std::string readFile(const char *filename);

class Shader {
public:
    GLuint ID{};

    Shader(const char *vertexPath, const char *fragmentPath);
    void Activate() const;
    void Delete() const;
};

#endif //OPENGL_HELLO_WORLD_SHADER_H
