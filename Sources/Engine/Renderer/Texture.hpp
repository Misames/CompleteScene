#pragma once

#include <vector>

using namespace std;

struct Texture
{
    const char *name;
    uint32_t id;

    static vector<Texture> textures;

    static void SetupManager();
    static uint32_t LoadTexture(const char *path);
    static uint32_t CheckExist(const char *path);
    static void PurgeTextures();
};