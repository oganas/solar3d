#version 420 core

in vec3 fragPosition;
in vec3 fragNormal;
in vec4 fragColour;

out vec4 outputColour;

uniform vec3 viewPosition;
uniform float shininess;
uniform float ambientStrength;
uniform float specularStrength;

struct Light {
    vec3 position;
    vec3 colour;
};

#define MAX_LIGHTS 4
uniform Light pointLights[MAX_LIGHTS]; 
uniform int numLights; 

void main() {
  vec3 totalLight = vec3(0.0);
  vec3 objectColour = vec3(fragColour.rgb);

  for(int i = 0; i < numLights; i++) {
      vec3 lightPos = pointLights[i].position;
      vec3 lightCol = pointLights[i].colour;
      
      vec3 N = normalize(fragNormal);
      vec3 L = normalize(lightPos - fragPosition);
      vec3 V = normalize(viewPosition - fragPosition);
      vec3 R = reflect(-L, N);

      vec3 ambient = ambientStrength * lightCol;

      float diff = max(dot(N, L), 0.0);
      vec3 diffuse = diff * lightCol;

      float spec = pow(max(dot(V, R), 0.0), shininess) * specularStrength;
      vec3 specular = spec * lightCol;

      totalLight += (ambient + diffuse + specular) * objectColour;
  }

  outputColour = vec4(totalLight, 1.0);
}
