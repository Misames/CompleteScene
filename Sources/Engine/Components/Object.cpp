#include <iostream>
#include "Vertex.hpp"

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
        transform->Release();
        delete transform;
        transform = nullptr;

        mesh->Release();
        delete mesh;
        mesh = nullptr;

        texture->Release();
        delete texture;
        texture = nullptr;

        shader->Release();
        delete shader;
        shader = nullptr;

        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);

        initialized = false;
        enabled = false;
        cout << "Object release" << endl;
    }
}

void Object::Initialize()
{
    if (initialized)
        Release();

    transform = new Transform();
    transform->Initialize();

    mesh = new Mesh();
    mesh->Initialize();

    texture = new Texture();
    texture->Initialize();

    shader = new GLShader();

#ifdef _DEBUG
    shader->LoadVertexShader("Sources/Shaders/vertex.glsl");
    shader->LoadFragmentShader("Sources/Shaders/fragment.glsl");
#else
    shader->LoadVertexShader("vertex.glsl");
    shader->LoadFragmentShader("fragment.glsl");
#endif

    shader->Initialize();
    program = shader->GetProgram();
    glUseProgram(program);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    positionLocation = glGetAttribLocation(program, "a_position");
    texCoordLocation = glGetAttribLocation(program, "a_texcoords");
    normalLocation = glGetAttribLocation(program, "a_normal");

    initialized = true;
    enabled = true;
    cout << "Object initialize" << endl;
}

void Object::Render() const
{
    if (enabled == false)
        return;

    glBindTexture(GL_TEXTURE_2D, texture->textureId);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->vertexs.size(), mesh->vertexs.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(positionLocation);
    glEnableVertexAttribArray(texCoordLocation);
    glEnableVertexAttribArray(normalLocation);

    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
    glVertexAttribPointer(texCoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));
    glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));

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

Transform *Object::GetTransform() const
{
    return transform;
}

Texture *Object::GetTexture() const
{
    return texture;
}
