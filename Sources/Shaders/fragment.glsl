#version 460 core

in vec2 v_texcoords;

uniform sampler2D u_sampler;

out vec4 fragColor;

void main()
{
    fragColor = texture(u_sampler, v_texcoords);
}