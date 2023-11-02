#version 460 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexcoords;

uniform mat4 uProjection;

out vec2 vTexcoords;

void main()
{
    gl_Position = uProjection * vec4(aPosition, 1.0);
    vTexcoords = aTexcoords;
}
