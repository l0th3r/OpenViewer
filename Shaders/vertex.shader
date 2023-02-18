#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

out vec3 color;
out vec2 texCoord;

uniform mat4 mtx_cam;

void main(void)
{
    gl_Position = mtx_cam * vec4(aPos, 1.0f);
    color = aColor;
    texCoord = aTex;
}
