#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//uniform mat4 mvp;
//projection * view * model *
void main()
{
    gl_Position = vec4(aPos, 1.0);
    TexCoord = vec2(aTexCoords.x, aTexCoords.y);
}