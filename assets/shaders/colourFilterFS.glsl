#version 150

out vec4 FragColor;
in vec2 textureCoords;

uniform sampler2D texture0;
uniform mat3 colourFilter = mat3(0.393, 0.769, 0.189,
	0.349, 0.686, 0.168,
	0.272, 0.534, 0.131);

void main()
{

	vec3 textureColour=texture(texture0, textureCoords).rgb;
	textureColour=textureColour*colourFilter;
	FragColor=vec4(textureColour,1.0f);
}
