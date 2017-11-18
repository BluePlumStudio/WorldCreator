#version 330 core
out vec4 color;
in vec2 texcoords_fs;

uniform sampler2D texture_main;

void main()
{
    color = texture(texture_main,texcoords_fs);
    //color=vec4(1.0f);
}