#version 460 core

layout (location = 0) in vec3 a_Position;

out vec4 Position;

void main() 
{
	Position = vec4(a_Position, 1.0);
}
