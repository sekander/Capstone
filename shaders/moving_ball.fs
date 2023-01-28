#version 330 core

#define center vec2(0.5, 0.5)
#define color1 vec4(0., 0., 1., 1.)
#define color2 vec4(1., 0., 0., 1.) 

#define res vec2(800, 600)

#define size 0.5
#define speed 5.
out vec4 fragColor;
in vec2 TexCoords;

uniform float time;

void main()
{
	vec2 uv = fragColor.xy/ res.xy;
	uv.x += sin(speed * time);
	fragColor = mix(color1, color2, (1./size) * distance(uv, center));

}
