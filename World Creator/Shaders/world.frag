#version 330 core

out vec4 color;

in vec2 texcoords_fs;
in vec3 normal_fs;
//in vec3 fragment_pos_fs;

uniform sampler2D texture_blocks;

float linearizeDepth(float depth)
{
    float near = 0.01f;
    float far = 128.0f;
    float z = depth * 2.0f - 1.0f; // Back to NDC
    return (2.0 * near) / (far + near - z * (far - near));
}

void main()
{
    vec4 tex=texture(texture_blocks,texcoords_fs);

    //Ambient
    vec3 ambient = vec3(tex) * 0.7f;
    //Diffuse
    vec3 lightDir=vec3(0.0f,1.0f,0.0f);
    vec3 diffuse=dot(normalize(normal_fs),lightDir) * vec3(tex) * 0.3f;

    float depth = linearizeDepth(gl_FragCoord.z) / 3.0f;

    color = vec4(depth)+vec4(ambient+diffuse,tex.w);
    //color=vec4(1.0f);
}