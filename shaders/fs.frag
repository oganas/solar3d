#version 420 core

in vec3 fragPosition;
in vec3 fragNormal;

out vec4 outputColour;

uniform vec3 objectColour;

struct Light { vec3 position; vec3 colour; };

uniform Light light;
uniform vec3 viewPosition;

void main() {
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * light.colour;

	vec3 norm = normalize(fragNormal);
	vec3 lightDir = normalize(light.position - fragPosition);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * light.colour;

	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPosition - fragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * light.colour;

  vec3 result = (ambient + diffuse + specular) * objectColour;
	outputColour = vec4(result, 1.0);
}
