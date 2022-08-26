#version 420 core
out vec4 FragColor;
  
in vec2 TexCoord;

uniform sampler2D texture0;
uniform bool textured;

void main()
{
	if(textured)
		FragColor = texture(texture0, TexCoord);
	else
		FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}