#pragma once

#include <stdint.h>
#include <GL/glew.h>

class Texture
{
private:
    bool initialized = false;
    int width;
    int height;
    int comp;
    uint8_t *data = nullptr;

public:
    GLuint textureId;

    ~Texture();
    void Initialize();
    void Release();
    void Load(const uint8_t color[4]);
    void LoadImage(const char *path);
};
