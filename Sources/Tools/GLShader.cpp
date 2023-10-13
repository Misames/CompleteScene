#include <fstream>
#include <iostream>
#include "GLShader.hpp"

using namespace std;

bool ValidateShader(GLuint shader)
{
    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (!compiled)
    {
        GLint infoLen = 0;

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

        if (infoLen > 1)
        {
            char *infoLog = new char[1 + infoLen];

            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            cout << "Error compiling shader: " << infoLog << endl;

            delete[] infoLog;
        }

        glDeleteShader(shader);

        return false;
    }

    return true;
}

bool GLShader::LoadVertexShader(const char *filename)
{
    ifstream fin(filename, ios::in | ios::binary);
    fin.seekg(0, ios::end);
    uint32_t length = (uint32_t)fin.tellg();
    fin.seekg(0, ios::beg);
    char *buffer = nullptr;
    buffer = new char[length + 1];
    buffer[length] = '\0';
    fin.read(buffer, length);

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &buffer, nullptr);
    glCompileShader(vertexShader);
    delete[] buffer;
    fin.close();

    return ValidateShader(vertexShader);
}

bool GLShader::LoadGeometryShader(const char *filename)
{
    ifstream fin(filename, ios::in | ios::binary);
    fin.seekg(0, ios::end);
    uint32_t length = (uint32_t)fin.tellg();
    fin.seekg(0, ios::beg);
    char *buffer = nullptr;
    buffer = new char[length + 1];
    buffer[length] = '\0';
    fin.read(buffer, length);

    geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometryShader, 1, &buffer, nullptr);
    glCompileShader(geometryShader);
    delete[] buffer;
    fin.close();

    return ValidateShader(geometryShader);
}

bool GLShader::LoadFragmentShader(const char *filename)
{
    ifstream fin(filename, ios::in | ios::binary);
    fin.seekg(0, ios::end);
    uint32_t length = (uint32_t)fin.tellg();
    fin.seekg(0, ios::beg);
    char *buffer = nullptr;
    buffer = new char[length + 1];
    buffer[length] = '\0';
    fin.read(buffer, length);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &buffer, nullptr);
    glCompileShader(fragmentShader);
    delete[] buffer;
    fin.close();

    return ValidateShader(fragmentShader);
}

bool GLShader::Create()
{
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, geometryShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    int32_t linked = 0;
    int32_t infoLen = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);

    if (!linked)
    {
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);

        if (infoLen > 1)
        {
            char *infoLog = new char[infoLen + 1];

            glGetProgramInfoLog(program, infoLen, NULL, infoLog);
            cout << "Error linkage shader: " << infoLog << endl;

            delete (infoLog);
        }

        glDeleteProgram(program);

        return false;
    }

    return true;
}

void GLShader::Destroy()
{
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);
    glDetachShader(program, geometryShader);
    glDeleteShader(geometryShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(program);
}