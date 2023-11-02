#version 460 core

in vec3 vTexcoords;

uniform samplerCube uCubemap;

out vec4 fragColor;

void main()
{
    fragColor = texture(uCubemap, vTexcoords);
}