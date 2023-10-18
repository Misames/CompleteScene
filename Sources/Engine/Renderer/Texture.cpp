#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include "OpenGL/OpenGLCore.hpp"
#include "Texture.hpp"

vector<Texture> Texture::textures;

uint32_t Texture::CheckExist(const char *path)
{
    for (Texture &tex : textures)
    {
        if (tex.name == path)
            return tex.id;
    }

    return 0;
}

void Texture::SetupManager()
{
    if (textures.size() == 0)
    {
        uint8_t data[] = {255, 255, 255, 255};
        uint32_t textureID = CreateTextureRGBA(1, 1, data);
        textures.push_back({"", textureID});
    }
}

void Texture::PurgeTextures()
{
    for (uint32_t i = 0; i < Texture::textures.size(); ++i)
        glDeleteTextures(1, &Texture::textures[i].id);
    textures.clear();
    textures.shrink_to_fit();
}

uint32_t Texture::LoadTexture(const char *path)
{
    uint32_t textureID = Texture::CheckExist(path);
    if (textureID > 0)
        return textureID;

    int width, height, c;
    uint8_t *data = stbi_load(path, &width, &height, &c, STBI_rgb_alpha);
    if (data == nullptr)
        return textures[0].id;

    textureID = CreateTextureRGBA(width, height, data, true);
    stbi_image_free(data);

    textures.push_back({path, textureID});
    return textureID;
}
