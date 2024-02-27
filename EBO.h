//
// Created by Hector Mejia on 2/26/24.
//

#ifndef OPENGL_HELLO_WORLD_EBO_H
#define OPENGL_HELLO_WORLD_EBO_H

#include <glad/glad.h>

class EBO {
public:
    // ID reference of Elements Buffer Object
    GLuint ID{};
    // Constructor that generates a Elements Buffer Object and links it to indices
    EBO(GLuint *indices, GLsizeiptr size);

    // Binds the EBO
    void Bind() const;
    // Unbinds the EBO
    void Unbind() const;
    // Deletes the EBO
    void Delete() const;
};


#endif //OPENGL_HELLO_WORLD_EBO_H
