#version 460 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texcoords;

out vec2 v_texcoords;

uniform mat4 u_projection;

void main()
{
    gl_Position = u_projection * vec4(a_position, 1.0);
    v_texcoords = a_texcoords;
}