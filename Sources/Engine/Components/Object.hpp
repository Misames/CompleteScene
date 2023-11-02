#pragma once

#include <GL/glew.h>
#include "Mesh.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "GLShader.hpp"

class Object
{
private:
    bool initialized = false;
    GLuint VAO, VBO, program;
    GLint positionLocation, normalLocation, texCoordLocation;

    GLShader *shader = nullptr;
    Mesh *mesh = nullptr;
    Transform *transform = nullptr;
    Texture *texture = nullptr;

public:
    bool enabled = false;

    ~Object();

    void Release();
    void Initialize();
    void Render() const;

    GLShader *GetShader() const;
    Mesh *GetMesh() const;
    Transform *GetTransform() const;
    Texture *GetTexture() const;
};