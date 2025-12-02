#version 420 core

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord;
in vec3 fragTangent;
in vec3 fragBitangent;

out vec4 outputColour;

// isLightSource is a bool that is passed in from c++ to determine if the object is a 
// light source or not, and thus if it's then ignore lighting effects only for it.
uniform bool isLightSource;


uniform vec3 viewPosition;

// Light struct for passing in c++ light data
struct Light { vec3 position; vec3 ambient; vec3 diffuse; vec3 specular; };
uniform Light light;

// Material struct for passing in c++ material data
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
    sampler2D textureSampler;
    int hasTexture;
    sampler2D normalMap;
    int hasNormal;
};
uniform Material material;

void main() {
	// Diffuse value check for object's diffuse colour or diffuse texture 
	// for later in the shader
  vec3 diffuseValue;
  if (material.hasTexture == 1) {
      diffuseValue = texture(material.textureSampler, fragTexCoord).rgb;
  } else {
      diffuseValue = material.diffuse;
  }

  // Light source check
  if (isLightSource) {
      outputColour = vec4(diffuseValue, 1.0);
      return;
  }

	/*
	 * Normal mapping
	 *
	 * Used the following for help:
	 * https://learnopengl.com/Lighting/Normal-Mapping
	 * https://www.youtube.com/watch?v=TnewxQxtoKs
   * https://www.youtube.com/watch?v=LRbgii6mVU4
   * https://stackoverflow.com/questions/29042849/implementing-normal-mapping-using-opengl-glsl
	 */
  vec3 norm = normalize(fragNormal);
  if (material.hasNormal == 1) {
    vec3 tangent = normalize(fragTangent);
    vec3 bitangent = normalize(fragBitangent);
    mat3 TBN = mat3(tangent, bitangent, norm);
    vec3 normalMap = texture(material.normalMap, fragTexCoord).rgb;
    normalMap = normalMap * 2.0 - 1.0;
    norm = normalize(TBN * normalMap);
  }

  // Ambient
  vec3 ambient = light.ambient * diffuseValue;

  // Diffuse
  vec3 lightDir = normalize(light.position - fragPosition);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = light.diffuse * (diff * diffuseValue);

  // Specular
  vec3 viewDir = normalize(viewPosition - fragPosition);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  vec3 specular = light.specular * (spec * material.specular);

  // Result
  vec3 result = ambient + diffuse + specular;
  outputColour = vec4(result, 1.0);
}
