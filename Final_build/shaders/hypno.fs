#version 330 core
// forked from https://www.shadertoy.com/view/MdsXzl

#define ITERATIONS 20.0
#define CIRCLES 20.0
//#define R 1.0
//#define G 0.0
//#define B 0.4

#define res vec2(800, 600)

out vec4 fragColor;
in vec2 TexCoords;

uniform float time;
uniform float R;
uniform float G;
uniform float B;

void main(  )
{
    vec2 uv = TexCoords.xy / res.xy;
    vec2 center = vec2(0.5, 0.5);
    float d = distance(uv, center) * CIRCLES;
    float adj = cos(time) * ITERATIONS;
    float i = 0.5 + sin(d + time + adj) / 2.0;
    float j = 0.5 + cos(d + time + adj) / 2.0;
    fragColor = vec4(R*j, G*(i + j), B*(i + j), 1.0);
}


