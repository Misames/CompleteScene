#include "Skybox.hpp"

Skybox::~Skybox()
{
    Release();
}

void Skybox::Initialize()
{
    if (initialized)
        Release();

    shader = new GLShader();
#ifdef _DEBUG
    shader->LoadVertexShader("Sources/Shaders/skybox_vertex.glsl");
    shader->LoadFragmentShader("Sources/Shaders/skybox_fragment.glsl");
    shader->Initialize();
#else
    shader->LoadVertexShader("skybox_vertex.glsl");
    shader->LoadFragmentShader("skybox_fragment.glsl");
    shader->Initialize();
#endif

    initialized = true;
}

void Skybox::Release()
{
    if (initialized)
    {
        shader->Release();
        delete shader;
        shader = nullptr;

        initialized = false;
    }
}

void Skybox::Render() const
{
}
