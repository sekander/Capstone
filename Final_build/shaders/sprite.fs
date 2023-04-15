#version 330 core
in vec2 TexCoords;
out vec4 fragColor;

uniform sampler2D sprite;
uniform vec3 color;

void main()
{
    
    fragColor = vec4(color, 1.0) * texture(sprite, TexCoords);
}
