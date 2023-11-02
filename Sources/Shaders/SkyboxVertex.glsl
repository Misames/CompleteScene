#version 460 core

layout (location = 0) in vec3 aPosition;

uniform mat4 uProjection;

out vec3 vTexcoords;

void main()
{
    gl_Position = uProjection * vec4(aPosition, 1.0);
    vTexcoords = aPosition;
}
