#version 420 core

in vec3 fragPosition;
in vec3 fragNormal;

out vec4 outputColour;

uniform vec3 viewPosition;

struct Light { vec3 position; vec3 ambient; vec3 diffuse; vec3 specular; };

uniform Light light;

struct Material { vec3 ambient; vec3 diffuse; vec3 specular; float shininess; };

uniform Material material;

void main() {
	float ambientStrength = 0.1;
  vec3 ambient  = light.ambient * material.ambient;

	vec3 norm = normalize(fragNormal);
	vec3 lightDir = normalize(light.position - fragPosition);
	float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse  = light.diffuse * (diff * material.diffuse);

	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPosition - fragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  vec3 specular = light.specular * (spec * material.specular);  

  vec3 result = ambient + diffuse + specular;
  result = clamp(result, 0.0, 1.0);
	outputColour = vec4(result, 1.0);
}
