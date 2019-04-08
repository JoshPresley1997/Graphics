#version 460

in vec3 Color;
in vec2 uvs;

out vec4 outColor;

uniform sampler2D in_texture;

void main()
{
	vec3 tmpColor = Color;
	tmpColor *= texture(in_texture, uvs).rgb;
	outColor = vec4(tmpColor, 1.0);
}