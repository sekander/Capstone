#version 330 core
//f0:x pos:
float f0 = 0.5;
//f1:y pos:
float f1 = 0.5;
//f2:ring size:
float f2 = 0.8;

#define res vec2(800, 600)

out vec4 fragColor;
in vec2 TexCoords;

uniform float time;


void main()
{
    float max_distance = 300.0/((res.x+res.y)/2.0) * 2. * f2;
    float dx = (f0 - TexCoords.x/res.x);
    float dy = (f1 - TexCoords.y/res.y);
    float pixDist = sqrt(pow(dx,2.0)+pow(dy,2.0));

    float color = 1.0-cos(2.0*3.14)*pixDist*5.0 ;
    float highlight = sin((time-pixDist)*10.0)*(1.0-min(pixDist/max_distance,1.0));

    fragColor = vec4(highlight, color * 0. , highlight + 0.5,1.0);
}

