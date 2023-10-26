#pragma once

#include <vector>
#include <GL/glew.h>
#include "GLShader.hpp"
#include "Texture.hpp"

using namespace std;

class Skybox
{
private:
    GLuint VBO;
    GLuint VAO;
    bool initialized = false;

    vector<Texture *> cubemap;
    GLShader *shader = nullptr;

public:
    bool enabled = false;

    ~Skybox();

    void Initialize();
    void Release();
    void Render() const;
};
