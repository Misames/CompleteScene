#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Texture.hpp"

Texture::Texture()
{
    std::cout << "Init Texture" << std::endl;
}

Texture::~Texture()
{
    Release();
    std::cout << "Destroy Texture" << std::endl;
}

void Texture::Initialize()
{
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::Release()
{
    delete[] data;
}
