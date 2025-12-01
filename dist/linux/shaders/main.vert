#version 420 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec3 fragNormal;
out vec3 fragPosition;
out vec2 fragTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * position;

	fragNormal = mat3(transpose(inverse(model))) * normal;
	fragPosition = vec3(model * position);
	fragTexCoord = texCoord;
}
