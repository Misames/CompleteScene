#pragma once

#include "GLShader.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "Transform.hpp"

class Object
{
private:
    bool initialized = false;
    GLuint VAO, VBO, program;
    GLint positionLocation, normalLocation, texCoordLocation;

    Transform *transform = nullptr;
    Mesh *mesh = nullptr;
    Texture *texture = nullptr;
    GLShader *shader = nullptr;

public:
    bool enabled = false;

    ~Object();
    void Initialize();
    void Release();
    void Render() const;
    Transform *GetTransform() const;
    Mesh *GetMesh() const;
    Texture *GetTexture() const;
    GLShader *GetShader() const;
};