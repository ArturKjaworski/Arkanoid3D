#version 330

out vec4 out_color;

uniform vec4 u_Color;
uniform sampler2D tex;

in vec2 UV;

void main()
{
	//out_color = u_Color;
	out_color = texture(tex, UV).rbga * u_Color;
}