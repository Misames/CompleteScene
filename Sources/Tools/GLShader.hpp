#pragma once

#include <GL/glew.h>

class GLShader
{
private:
    GLuint program;
    GLuint vertexShader;
    GLuint geometryShader;
    GLuint fragmentShader;

public:
    GLShader() : program(0), vertexShader(0), geometryShader(0), fragmentShader(0) {}
    ~GLShader() {}
    inline GLuint GetProgram() { return program; }
    bool LoadVertexShader(const char *filename);
    bool LoadGeometryShader(const char *filename);
    bool LoadFragmentShader(const char *filename);
    bool Create();
    void Destroy();
};