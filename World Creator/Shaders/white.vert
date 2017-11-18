#version 330 core
layout (location = 0) in vec3 position_vs;

void main()
{
    gl_Position = vec4(position_vs, 1.0f);
}