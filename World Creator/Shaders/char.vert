#version 330 core
layout (location = 0) in vec2 position_vs;
layout (location = 1) in vec2 texcoords_vs;
layout (location = 2) in vec4 color_vs;

out vec2 texcoords_fs;
out vec4 color_fs;

uniform mat4 MVP_vs;

void main()
{
    gl_Position = MVP_vs*vec4(position_vs.x,position_vs.y,0.0f, 1.0f);
    texcoords_fs=texcoords_vs;
    color_fs=color_vs;
}