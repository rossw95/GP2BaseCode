#version 150

out vec4 FragColor;
in vec3 worldNormal;
in vec3 cameraDirectionOut;

uniform vec3 lightDirection;

uniform vec4 ambientMaterialColour;
uniform vec4 diffuseMaterialColour;
uniform vec4 specularMaterialColour;
uniform float specularPower;

uniform vec4 ambientLightColour;
uniform vec4 diffuseLightColour;
uniform vec4 specularLightColour;

uniform sampler1D toonShade;
uniform float numberOfColours;

void main()
{
	vec3 lightDirectionNormalized=normalize(lightDirection);
	float diffuseTerm = max(dot(worldNormal, lightDirectionNormalized),0.0f);
	vec3 halfWayVec = normalize(cameraDirectionOut + lightDirectionNormalized);
	float specularTerm = pow(max(dot(worldNormal, halfWayVec),0.0f), specularPower);

	float shadeIntensity=diffuseTerm;
	vec3 shade=vec3(1.0f,1.0f,1.0f);
	if (shadeIntensity<0.5 && shadeIntensity>0.2)
		shade=vec3(0.5f,0.5f,0.5f);
	if (shadeIntensity<0.2)
		shade=vec3(0.2f,0.2f,0.2f);

	FragColor = (ambientMaterialColour*ambientLightColour) +
	(diffuseMaterialColour*vec4(shade,1.0f)) +
	(specularMaterialColour*specularLightColour*specularTerm);
}
