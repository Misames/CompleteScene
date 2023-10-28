#pragma once

#include <GL/glew.h>
#include "GLShader.hpp"

class Skybox
{
private:
    bool initialized = false;
    GLShader *shader = nullptr;
    GLuint textureId;
    GLuint program;

public:
    bool enabled = false;

    ~Skybox();
    void Initialize();
    void Release();
    void Render() const;
};
