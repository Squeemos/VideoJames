#version 410 core
out vec4 FragColor;
  
in vec2 TexCoord;

uniform sampler2D texture0;
uniform int texture_or_color;

void main()
{
	if(texture_or_color == 1)
		FragColor = texture(texture0, TexCoord);
	else
		FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}