#version 420 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;

out vec3 fragPosition;
out vec2 fragTexCoord;
out vec3 fragNormal;
out vec3 fragTangent;
out vec3 fragBitangent;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  vec4 worldPos = model * vec4(position, 1.0);
  fragPosition = vec3(worldPos);

  fragTexCoord = texCoord;

 /*
  * Normal mapping
  * 
  * Used the following for help:
  * https://learnopengl.com/Lighting/Normal-Mapping
  * https://www.youtube.com/watch?v=TnewxQxtoKs
  * https://www.youtube.com/watch?v=LRbgii6mVU4
  * https://stackoverflow.com/questions/29042849/implementing-normal-mapping-using-opengl-glsl
  * https://www.opengl-tutorial.org/intermediate-tutorials/tutorial-13-normal-mapping/
  */
  mat3 normalMatrix = transpose(inverse(mat3(model)));
  fragNormal = normalize(normalMatrix * normal);
  fragTangent = normalize(normalMatrix * tangent);
  fragBitangent = normalize(normalMatrix * bitangent);

  gl_Position = projection * view * worldPos;
}
