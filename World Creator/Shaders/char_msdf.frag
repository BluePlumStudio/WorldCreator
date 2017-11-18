#version 330 core

out vec4 color;

in vec2 texcoords_fs;
in vec4 color_fs;

uniform sampler2D texture_text;

float median(float r, float g, float b)
{
    return max(min(r, g), min(max(r, g), b));
}

void main()
{
    
    //vec4 sampled = texture(texture_text, texcoords_fs);

    //color = color_fs * sampled;

    vec3 sample = texture(texture_text, texcoords_fs).rgb;
    float sigDist = median(sample.r, sample.g, sample.b) - 0.5;
    float opacity = clamp(sigDist/fwidth(sigDist) + 0.5, 0.0, 1.0);
    color = color_fs * opacity;
    //color = mix(vec4(0.0f,0.0f,1.0f,0.0f), color_fs, opacity);
}