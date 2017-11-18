#version 330 core

out vec4 color;

in vec2 texcoords_fs;
in vec4 color_fs;

uniform sampler2D texture_text;

void main()
{
    color = color_fs * texture(texture_text, texcoords_fs);
    //color=vec4(1.0f);
}