#version 410 core
out vec4 FragColor;
  
in vec2 TexCoord;

uniform sampler2D texture0;
uniform int texture_or_color;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

void main()
{
	if(texture_or_color == 1)
		FragColor = texture(texture0, TexCoord);
	else
		FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}