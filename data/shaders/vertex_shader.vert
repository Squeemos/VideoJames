#version 420 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 projection_view;
uniform vec3 color;

void main()
{
	gl_Position = projection_view * model * vec4(aPos, 1.0);
	ourColor = color;
	TexCoord = aTexCoord;
}