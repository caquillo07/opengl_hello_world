//
// Created by Hector Mejia on 2/27/24.
//

#ifndef OPENGL_HELLO_WORLD_TEXTURE_H
#define OPENGL_HELLO_WORLD_TEXTURE_H

#include <glad/glad.h>
#include "shader.h"

class Texture {
public:
    GLuint ID{};
    GLenum type{};
    Texture(const char *image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

    // Assigns a texture unit to a texture
    void texUnit(Shader &shader, const char *uniform, GLint unit) const;
    // Binds a texture
    void Bind() const;
    // Unbinds a texture
    void Unbind() const;
    // Deletes a texture
    void Delete() const;
};


#endif //OPENGL_HELLO_WORLD_TEXTURE_H
