#include <iostream>
#include <stb/stb_image.h>
#include "GLShader.hpp"

#include "Skybox.hpp"

using namespace std;

Skybox::~Skybox()
{
    Release();
}

void Skybox::Initialize()
{
    if (initialized)
        Release();

    shader = new GLShader();
    if (!shader)
        throw bad_alloc();

#ifdef _DEBUG
    shader->LoadVertexShader("Sources/Shaders/SkyboxVertex.glsl");
    shader->LoadFragmentShader("Sources/Shaders/SkyboxFragment.glsl");
#else
    shader->LoadVertexShader("SkyboxVertex.glsl");
    shader->LoadFragmentShader("SkyboxFragment.glsl");
#endif

    shader->Initialize();
    program = shader->GetProgram();
    glUseProgram(program);

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

    const char *faces[6] = {"back", "bottom", "front", "left", "right", "top"};
    int32_t width, height, nrChannels;
    for (uint32_t i = 0; i < 6; ++i)
    {
        string path = "Sources/Assets/Textures/skybox/" + string(faces[i]) + ".jpg";
        uint8_t *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, width, height, 0, GL_RGBA8, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            cout << "Erreur lors du chargement de la texture: " << faces[i] << endl;
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    initialized = true;
    cout << "Skybox initialize" << endl;
}

void Skybox::Release()
{
    if (initialized)
    {
        if (shader)
        {
            shader->Release();
            delete shader;
            shader = nullptr;
        }

        initialized = false;
        cout << "Skybox release" << endl;
    }
}

void Skybox::Render() const {}
