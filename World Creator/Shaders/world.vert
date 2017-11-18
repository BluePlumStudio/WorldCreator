#version 330 core
layout (location = 0) in vec3 position_vs;
layout (location = 1) in vec2 texcoords_vs;
layout (location = 2) in vec3 normal_vs;

out vec2 texcoords_fs;
out vec3 normal_fs;
//out vec3 fragment_pos_fs;

uniform mat4 MVP_vs;
uniform mat4 MV_vs;
uniform mat4 normal_mat_vs;

void main()
{
    gl_Position = MVP_vs*vec4(position_vs, 1.0f);

    texcoords_fs=texcoords_vs;
    normal_fs=mat3(normal_mat_vs) * normal_vs;
    //fragment_pos_fs=vec3(MV_vs * vec4(position_vs, 1.0f));
}