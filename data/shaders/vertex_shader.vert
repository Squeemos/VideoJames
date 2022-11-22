#version 420 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 world_projection;
uniform mat4 screen_projection;
uniform mat4 view;
uniform mat4 rotation;

uniform mat4 model; 
uniform vec3 color;

uniform bool screen_or_world;

void main()
{
	if(screen_or_world)
		gl_Position = world_projection * view * rotation * model * vec4(aPos, 1.0);
	else
		gl_Position = screen_projection * model * vec4(aPos, 1.0);
	ourColor = color;
	TexCoord = aTexCoord;
}