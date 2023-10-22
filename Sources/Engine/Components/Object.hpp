#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "IEntity.hpp"
#include "Mesh.hpp"
#include "../../Tools/GLShader.hpp"

class Object : IEntity
{
private:
    Mesh *mesh;
    GLShader *shader;
    GLuint VBO, VAO;
    GLint positionLocation, normalLocation, texCoordLocation;

public:
    ~Object() override;
    void Release() final;
    void Initialize() final;
    void Render();
    GLShader *GetShader() const;
};