#pragma once

#include <stdint.h>
#include <GL/glew.h>

class Texture
{
private:
    uint8_t data[4] = {255, 255, 255, 255};

public:
    GLuint textureId;

    Texture();
    void Load(uint8_t color[4]);
};
