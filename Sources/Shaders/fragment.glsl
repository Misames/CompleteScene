#version 460 core

in vec2 v_texcoords;

out vec4 fragColor;

uniform sampler2D u_sampler;

void main()
{
    fragColor = texture(u_sampler, v_texcoords);
}