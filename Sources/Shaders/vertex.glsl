#version 460 core

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec2 a_texcoords;

out vec2 v_texcoords;

uniform mat4 u_projection;

void main()
{
    gl_Position = u_projection * a_position;
    v_texcoords = a_texcoords;
}