//
// Created by Hector Mejia on 2/26/24.
//

#include "VAO.h"

// Constructor that generates a VAO ID
VAO::VAO() {
    glGenVertexArrays(1, &ID);
}

// Links a VBO to the VAO using a certain layout
void VAO::LinkVBO(VBO &VBO, GLuint layout) const {
    VBO.Bind();
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}

// Binds the VAO
void VAO::Bind() const {
    glBindVertexArray(ID);
}

// Unbinds the VAO
void VAO::Unbind() const {
    glBindVertexArray(0);
}

// Deletes the VAO
void VAO::Delete() const {
    glDeleteVertexArrays(1, &ID);
}
