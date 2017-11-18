#version 330 core

out vec4 color;

in vec2 texcoords_fs;
in vec4 color_fs;

uniform sampler2D texture_GUI;

void main()
{
    color = color_fs * texture(texture_GUI, texcoords_fs);
    //color = color_fs;
}