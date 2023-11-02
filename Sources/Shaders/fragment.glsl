#version 460 core

in vec2 vTexcoords;

uniform sampler2D uSampler;

out vec4 fragColor;

void main()
{
    fragColor = texture(uSampler, vTexcoords);
}
