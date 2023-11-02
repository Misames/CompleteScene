#pragma once

class Skybox
{
private:
    bool initialized = false;
    GLuint program, textureId;
    GLShader *shader = nullptr;

public:
    bool enabled = false;

    ~Skybox();
    void Initialize();
    void Release();
    void Render() const;
};
