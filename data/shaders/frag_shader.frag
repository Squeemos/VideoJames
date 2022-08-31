#version 420 core
out vec4 FragColor;
  
in vec2 TexCoord;
in vec3 ourColor;

uniform sampler2D texture0;
uniform bool textured;

void main()
{
	if(textured)
		FragColor = texture(texture0, TexCoord);
	else
		FragColor = vec4(ourColor, 1.0);
}