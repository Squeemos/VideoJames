#version 410 core
out vec4 FragColor;
  
in vec2 TexCoord;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

uniform sampler2D texture1;
uniform int textured;

void main()
{
	if(textured == 1)
		FragColor = texture(texture1, TexCoord);
	else
		FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}