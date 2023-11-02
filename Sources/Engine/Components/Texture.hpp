#pragma once

class Texture
{
private:
    bool initialized = false;
    uint8_t *data = nullptr;

public:
    GLuint textureId;

    ~Texture();
    void Initialize();
    void Release();
    void Load(const uint8_t color[4]) const;
    void LoadImage(const char *path);
};
