#pragma once

#include <GL/glew.h>

class Mesh;
class GLShader;

class Axes
{
private:
    bool initialized = false;
    GLuint VAO, VBO, program;
    GLint positionLocation, colorLocation;
    GLShader *shader = nullptr;

public:
    bool enabled = false;

    ~Axes();
    void Initialize();
    void Release();
    void Render(int, int) const;

    GLShader *GetShader() const;
};
