#version 330 core

out vec4 color;

in vec2 texcoords_fs;

uniform sampler2D texture_screen;
uniform int window_width;
uniform int window_height;



void main()
{
	float x=gl_FragCoord.x-window_width / 2.0f;
	float y=gl_FragCoord.y-window_height / 2.0f;
	float r=window_width / 2.0f;
	float distanceS=x * x + 3.6f * y * y;
	float rS=r*r;
    if(distanceS >= rS)
	{
		float offset = 0.002f * distanceS / rS;
		vec2 offsets[9] = vec2[](
			vec2(-offset, offset),  // top-left
			vec2(0.0f,    offset),  // top-center
			vec2(offset,  offset),  // top-right
			vec2(-offset, 0.0f),    // center-left
			vec2(0.0f,    0.0f),    // center-center
			vec2(offset,  0.0f),    // center-right
			vec2(-offset, -offset), // bottom-left
			vec2(0.0f,    -offset), // bottom-center
			vec2(offset,  -offset)  // bottom-right
		);

		float kernel[9] = float[](
		0.0625f,0.125f,0.0625f,
		0.125f,0.25f,0.125f,
		0.0625f,0.125f,0.0625f
		);

		vec3 sampleTex[9];

		for(int i = 0; i < 9; i++)
		{
			sampleTex[i] = vec3(texture(texture_screen, texcoords_fs + offsets[i]));
		}

		vec3 col = vec3(0.0);
		for(int i = 0; i < 9; i++)
		{
			col += sampleTex[i] * kernel[i];
		}

		color=vec4(col,1.0f);
	}
	else
	{
		color=texture(texture_screen,texcoords_fs);
	}
}