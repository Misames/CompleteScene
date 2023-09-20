#include <fstream>
#include <iostream>
#include "GLShader.hpp"

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
            std::cout << "Error compiling shader:" << infoLog << std::endl;

            delete[] infoLog;
        }

        // on supprime le shader object car il est inutilisable
        glDeleteShader(shader);

        return false;
    }

    return true;
}

bool GLShader::LoadVertexShader(const char *filename)
{
    // 1. Charger le fichier en memoire
    std::ifstream fin(filename, std::ios::in | std::ios::binary);
    fin.seekg(0, std::ios::end);
    uint32_t length = (uint32_t)fin.tellg();
    fin.seekg(0, std::ios::beg);
    char *buffer = nullptr;
    buffer = new char[length + 1];
    buffer[length] = '\0';
    fin.read(buffer, length);

    // 2. Creer le shader object
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &buffer, nullptr);
    // 3. Le compiler
    glCompileShader(vertexShader);
    // 4. Nettoyer
    delete[] buffer;
    fin.close(); // non obligatoire ici

    // 5.
    // verifie le status de la compilation
    return ValidateShader(vertexShader);
}

bool GLShader::LoadGeometryShader(const char *filename)
{
    // 1. Charger le fichier en memoire
    std::ifstream fin(filename, std::ios::in | std::ios::binary);
    fin.seekg(0, std::ios::end);
    uint32_t length = (uint32_t)fin.tellg();
    fin.seekg(0, std::ios::beg);
    char *buffer = nullptr;
    buffer = new char[length + 1];
    buffer[length] = '\0';
    fin.read(buffer, length);

    // 2. Creer le shader object
    geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometryShader, 1, &buffer, nullptr);
    // 3. Le compiler
    glCompileShader(geometryShader);
    // 4. Nettoyer
    delete[] buffer;
    fin.close(); // non obligatoire ici

    // 5.
    // verifie le status de la compilation
    return ValidateShader(geometryShader);
}

bool GLShader::LoadFragmentShader(const char *filename)
{
    std::ifstream fin(filename, std::ios::in | std::ios::binary);
    fin.seekg(0, std::ios::end);
    uint32_t length = (uint32_t)fin.tellg();
    fin.seekg(0, std::ios::beg);
    char *buffer = nullptr;
    buffer = new char[length + 1];
    buffer[length] = '\0';
    fin.read(buffer, length);

    // 2. Creer le shader object
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &buffer, nullptr);
    // 3. Le compiler
    glCompileShader(fragmentShader);
    // 4. Nettoyer
    delete[] buffer;
    fin.close(); // non obligatoire ici

    // 5.
    // verifie le status de la compilation
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
    // verification du statut du linkage
    glGetProgramiv(program, GL_LINK_STATUS, &linked);

    if (!linked)
    {
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);

        if (infoLen > 1)
        {
            char *infoLog = new char[infoLen + 1];

            glGetProgramInfoLog(program, infoLen, NULL, infoLog);
            std::cout << "Erreur de lien du programme: " << infoLog << std::endl;

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