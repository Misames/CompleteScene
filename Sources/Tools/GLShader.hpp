#pragma once

#include <fstream>
#include <iostream>
#include <GL/glew.h>

using namespace std;

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
    inline GLuint GetProgram() { return program; }
    bool LoadVertexShader(const char *filename);
    bool LoadGeometryShader(const char *filename);
    bool LoadFragmentShader(const char *filename);
    bool Initialize();
    void Release();
};