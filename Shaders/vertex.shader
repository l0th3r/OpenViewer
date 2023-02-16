#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

out vec3 color;
out vec2 texCoord;

uniform float scale;

uniform mat4 mtx_model;
uniform mat4 mtx_view;
uniform mat4 mtx_proj;

void main(void)
{
    gl_Position = mtx_proj * mtx_view * mtx_model * vec4(aPos, 1.0f);
    color = aColor;
    texCoord = aTex;
}
