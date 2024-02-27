//
// Created by Hector Mejia on 2/26/24.
//

#ifndef OPENGL_HELLO_WORLD_VBO_H
#define OPENGL_HELLO_WORLD_VBO_H

#include <glad/glad.h>

class VBO {
public:
    GLuint ID{};

    VBO(GLfloat* vertices, GLsizeiptr size);
    void Bind() const;
    void Unbind() const;
    void Delete() const;
};

#endif //OPENGL_HELLO_WORLD_VBO_H
