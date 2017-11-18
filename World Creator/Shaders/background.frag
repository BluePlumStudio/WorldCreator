#version 330 core
out vec4 color;
in vec2 texcoords_fs;

uniform sampler2D texture_main;

void main()
{
	const float offset = 0.8f / 250.0f;
	vec2 offsets[9] = vec2[](
		vec2(-offset, offset),  // top-left
		vec2(0.0f, offset),  // top-center
		vec2(offset, offset),  // top-right
		vec2(-offset, 0.0f),    // center-left
		vec2(0.0f, 0.0f),    // center-center
		vec2(offset, 0.0f),    // center-right
		vec2(-offset, -offset), // bottom-left
		vec2(0.0f, -offset), // bottom-center
		vec2(offset, -offset)  // bottom-right
		);

	float kernel[9] = float[](
		0.0625f, 0.125f, 0.0625f,
		0.125f, 0.25f, 0.125f,
		0.0625f, 0.125f, 0.0625f
		);

	vec3 sampleTex[9];

	for (int i = 0; i < 9; i++)
	{
		sampleTex[i] = vec3(texture(texture_main, texcoords_fs + offsets[i]));
	}

	vec3 col = vec3(0.0);
	for (int i = 0; i < 9; i++)
	{
		col += sampleTex[i] * kernel[i];
	}

	color = vec4(col, 1.0f);
	//color=vec4(1.0f);
}