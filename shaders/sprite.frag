#version 330 core
in vec2 pos;

out vec4 color;

uniform vec3 spriteColor;
 
void main()
{    
    float rsq = dot(pos, pos);
    if (rsq > 1)
        discard;    
    color = vec4(spriteColor, 1.0);
}  