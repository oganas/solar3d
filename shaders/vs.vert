#version 420 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 colour;

out vec4 fcolour;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	gl_Position = projection * view * model * position;

	fcolour = colour;
}
