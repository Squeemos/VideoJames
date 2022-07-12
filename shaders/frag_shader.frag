#version 410 core
out vec4 FragColor;

uniform vec4 our_color;

void main()
{
	FragColor = our_color;
}