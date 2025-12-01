#version 420 core

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord;

out vec4 outputColour;

uniform bool isLightSource;

uniform vec3 viewPosition;

struct Light { vec3 position; vec3 ambient; vec3 diffuse; vec3 specular; };

uniform Light light;

struct Material { vec3 ambient; vec3 diffuse; vec3 specular; float shininess; sampler2D textureSampler; int hasTexture; };

uniform Material material;

void main() {
	vec3 diffuseValue;
	if (material.hasTexture == 1) {
		diffuseValue = texture(material.textureSampler, fragTexCoord).rgb;
	} else {
		diffuseValue = material.diffuse;
	}

	// ambient
  vec3 ambient  = light.ambient * diffuseValue;

	// diffuse
	vec3 norm = normalize(fragNormal);
	vec3 lightDir = normalize(light.position - fragPosition);
	float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse  = light.diffuse * (diff * diffuseValue);

	// specular
	vec3 viewDir = normalize(viewPosition - fragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  vec3 specular = light.specular * (spec * material.specular);  

	// final colour
  vec3 result = ambient + diffuse + specular;
	outputColour = vec4(result, 1.0);
}
