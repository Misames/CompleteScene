#version 460 core

out vec3 TexCoords;

void main()
{
    TexCoords = vec3(gl_Position);
}
