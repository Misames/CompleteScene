#version 460 core

layout(location = 0) in vec3 inPosition; // Attribut d'entrée pour les positions des vertices

void main()
{
    gl_Position = vec4(inPosition, 1.0); // Transforme la position du vertex
}