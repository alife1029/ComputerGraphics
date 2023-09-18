#version 460 core

in vec4 v_Color;
in vec2 v_TexCoords;

uniform sampler2D u_Texture;

void main()
{
	vec4 sampled = texture(u_Texture, v_TexCoords);
	gl_FragColor = sampled * v_Color;
}
