#version 460

in vec3 position;
in vec3 color;
in vec3 lightColor;

out vec3 Color;

uniform mat4 mvpMatrix;

void main()
{
	float ambientIntenstity = 0.5;
	Color = ambientIntenstity * lightColor * color;
	gl_Position = mvpMatrix * vec4(position, 1.0);
    
    
}