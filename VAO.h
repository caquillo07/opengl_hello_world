//
// Created by Hector Mejia on 2/26/24.
//

#ifndef OPENGL_HELLO_WORLD_VAO_H
#define OPENGL_HELLO_WORLD_VAO_H

#include<glad/glad.h>
#include"VBO.h"

class VAO {
public:
    // ID reference for the Vertex Array Object
    GLuint ID{};
    // Constructor that generates a VAO ID
    VAO();

    // Links a VBO to the VAO using a certain layout
    void LinkVBO(VBO &VBO, GLuint layout) const;
    // Binds the VAO
    void Bind() const;
    // Unbinds the VAO
    void Unbind() const;
    // Deletes the VAO
    void Delete() const;
};

#endif //OPENGL_HELLO_WORLD_VAO_H
