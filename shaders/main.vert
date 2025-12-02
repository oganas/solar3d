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

void main()
{
    vec4 worldPos = model * vec4(position, 1.0);
    fragPosition = vec3(worldPos);

    // Pass UVs
    fragTexCoord = texCoord;

    // Transform normals, tangent, bitangent to world space
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    fragNormal = normalize(normalMatrix * normal);
    fragTangent = normalize(normalMatrix * tangent);
    fragBitangent = normalize(normalMatrix * bitangent);

    // Standard MVP transform
    gl_Position = projection * view * worldPos;
}
