#version 330 core
layout (location = 0) in vec3 aPos;


uniform mat4 model;
// note that we're omitting the view matrix; the view never changes so we basically have an identity view matrix and can therefore omit it.
uniform mat4 projection;


void main()
{
       //gl_Position =  vec4(aPos.x, aPos.y, aPos.z, 1.0);
       gl_Position =  projection * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
