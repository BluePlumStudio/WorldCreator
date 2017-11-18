#version 330 core
layout (location = 0) in vec3 position_vs;
layout (location = 1) in vec2 texcoords_vs;

out vec2 texcoords_fs;

uniform mat4 MVP_vs;

void main()
{
    gl_Position = MVP_vs*vec4(position_vs, 1.0f);
    texcoords_fs=texcoords_vs;
}