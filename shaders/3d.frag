#version 410 core

out vec4 FragColor;

in vec2 TexCoords;

uniform vec4 other_color;
uniform int textured;
uniform sampler2D texture_diffuse1;

void main()
{    
	if (textured == 1)
		FragColor = texture(texture_diffuse1, TexCoords);
	else
		FragColor = other_color;
}