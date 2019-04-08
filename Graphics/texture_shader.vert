#version 460

in vec3 position;
in vec3 color;
in vec3 lightColor;
in vec2 uv;

out vec3 Color;
out vec2 uvs;
uniform mat4 mvpMatrix;

void main()
{
	float ambientIntenstity = 0.5;
	Color = ambientIntenstity * lightColor * color;
	uvs = uv;
	gl_Position = mvpMatrix * vec4(position, 1.0);
    
    
}