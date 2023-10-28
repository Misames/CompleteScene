#version 460 core

layout (location = 0) in vec3 a_position;

uniform mat4 u_projection;

out vec3 v_texcoords;

void main()
{
    gl_Position = u_projection * vec4(a_position, 1.0);
    v_texcoords = a_position;
}
