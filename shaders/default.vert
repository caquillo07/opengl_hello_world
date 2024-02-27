#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

// the color can only be used in the fragment shader, but because the pipeline
// starts with the vertex shader, we need to pass the color above to the fragment
// shader
out vec3 color;

uniform float scale;

void main() {
    gl_Position = vec4(aPos.x * scale, aPos.y * scale, aPos.z * scale, 1.0);
    color = aColor;
}
