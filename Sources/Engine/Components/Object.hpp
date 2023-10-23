#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "IEntity.hpp"
#include "Mesh.hpp"
#include "Transform.hpp"
#include "../../Tools/GLShader.hpp"

class Object : IEntity
{
private:
    Transform *transform = nullptr;
    Mesh *mesh = nullptr;
    GLShader *shader = nullptr;
    GLuint VBO, VAO;
    GLint positionLocation, normalLocation, texCoordLocation;

public:
    ~Object() override;
    void Release() final;
    void Initialize() final;
    void Render();

    GLShader *GetShader() const;
    Mesh *GetMesh() const;
};