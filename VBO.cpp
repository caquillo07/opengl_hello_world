//
// Created by Hector Mejia on 2/26/24.
//

#include "VBO.h"

VBO::VBO(GLfloat *vertices, GLsizeiptr size) {
    glGenBuffers(1, &this->ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, this->ID);
}

void VBO::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() const {
    glDeleteBuffers(1, &this->ID);
}

