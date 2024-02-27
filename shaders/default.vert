#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

// the color can only be used in the fragment shader, but because the pipeline
// starts with the vertex shader, we need to pass the color above to the fragment
// shader
out vec3 color;
out vec2 texCoord;

uniform float scale;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0); // remember the order of multiplication
    color = aColor;
    texCoord = aTexCoord;
}
