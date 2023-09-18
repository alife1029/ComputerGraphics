#version 460 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TexCoords;

out vec4 v_Color;
out vec2 v_TexCoords;

uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

void main() 
{
	v_Color = a_Color;
	v_TexCoords = a_TexCoords;
	gl_Position = u_ProjectionMatrix * u_ViewMatrix * vec4(a_Position, 1.0);
}
