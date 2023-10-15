#pragma once

class Texture
{
private:
    unsigned int textureId;
    int width;
    int height;
    int channel;
    unsigned char *data = new unsigned char[4]{255, 0, 255, 255};

public:
    Texture();
    ~Texture();
    void Initialize();
    void Release();
};
