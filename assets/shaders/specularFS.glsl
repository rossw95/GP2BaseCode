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

void main()
{
	float diffuseTerm = dot(worldNormal, lightDirection);
	vec3 halfWayVec = normalize(cameraDirectionOut + lightDirection);
	float specularTerm = pow(dot(worldNormal, halfWayVec), specularPower);

	FragColor = (ambientMaterialColour*ambientLightColour) + (diffuseMaterialColour*diffuseLightColour*diffuseTerm) + (specularMaterialColour*specularLightColour*specularTerm);
}
