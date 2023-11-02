#pragma once

#include <GL/glew.h>

class GLShader
{
private:
    GLuint program;
    GLuint vertexShader;
    GLuint geometryShader;
    GLuint fragmentShader;
    bool initialized = false;

public:
    GLShader();
    ~GLShader();
    bool Initialize();
    void Release();
    bool LoadVertexShader(const char *filename);
    bool LoadGeometryShader(const char *filename);
    bool LoadFragmentShader(const char *filename);
    inline GLuint GetProgram() { return program; }
};