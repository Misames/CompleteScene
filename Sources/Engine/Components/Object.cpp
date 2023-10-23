#include <iostream>
#include "Object.hpp"

using namespace std;

Object::~Object()
{
    Release();
}

void Object::Release()
{
    if (initialized)
    {
        shader->Release();
        mesh->Release();
        delete shader, mesh;
        shader, mesh = nullptr;
        initialized, enabled = false;
        cout << "Object release" << endl;
    }
}

void Object::Initialize()
{
    if (initialized)
        Release();

    // Init Buffers
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    mesh = new Mesh();
    mesh->Initialize();
    shader = new GLShader();
#ifdef _DEBUG
    shader->LoadVertexShader("Sources/Shaders/vertex.glsl");
    shader->LoadFragmentShader("Sources/Shaders/fragment.glsl");
    shader->Initialize();
#else
    shader->LoadVertexShader("vertex.glsl");
    shader->LoadFragmentShader("fragment.glsl");
    shader->Initialize();
#endif

    initialized, enabled = true;
    cout << "Object initialize" << endl;
}

void Object::Render()
{
    if (enabled == false)
        return;

    GLuint program = shader->GetProgram();
    glUseProgram(program);

    constexpr int STRIDE = sizeof(Vertex);
    glBufferData(GL_ARRAY_BUFFER, STRIDE * mesh->vertexs.size(), mesh->vertexs.data(), GL_STATIC_DRAW);

    positionLocation = glGetAttribLocation(program, "a_position");
    texCoordLocation = glGetAttribLocation(program, "a_texcoords");
    normalLocation = glGetAttribLocation(program, "a_normal");

    glEnableVertexAttribArray(positionLocation);
    glEnableVertexAttribArray(texCoordLocation);
    glEnableVertexAttribArray(normalLocation);

    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, STRIDE, (void *)offsetof(Vertex, position));
    glVertexAttribPointer(texCoordLocation, 2, GL_FLOAT, GL_FALSE, STRIDE, (void *)offsetof(Vertex, uv));
    glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, STRIDE, (void *)offsetof(Vertex, normal));

    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(mesh->vertexs.size()));

    glDisableVertexAttribArray(positionLocation);
    glDisableVertexAttribArray(texCoordLocation);
    glDisableVertexAttribArray(normalLocation);
}

GLShader *Object::GetShader() const
{
    return shader;
}

Mesh *Object::GetMesh() const
{
    return mesh;
}
