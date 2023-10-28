#pragma once

#include <GL/glew.h>
#include "Mesh.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "GLShader.hpp"

class Object
{
private:
    GLuint VAO;
    GLuint VBO;
    GLuint program;
    GLint positionLocation;
    GLint normalLocation;
    GLint texCoordLocation;
    bool initialized = false;

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