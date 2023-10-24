#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Mesh.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "../../Tools/GLShader.hpp"

using namespace std;

class Object
{
private:
    GLuint VBO;
    GLuint VAO;
    GLint positionLocation;
    GLint normalLocation;
    GLint texCoordLocation;

    GLShader *shader = nullptr;
    Mesh *mesh = nullptr;
    Transform *transform = nullptr;
    Texture *texture = nullptr;

public:
    bool enabled = false;
    bool initialized = false;

    ~Object();

    void Release();
    void Initialize();
    void Render();

    GLShader *GetShader() const;
    Mesh *GetMesh() const;
    Transform *GetTransform() const;
    Texture *GetTexture() const;
};