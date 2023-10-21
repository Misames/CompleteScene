#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "IRenderingEngine.hpp"
#include "Texture.hpp"
#include "../Components/Camera.hpp"
#include "../Components/Mesh.hpp"
#include "../../Tools/GLShader.hpp"

using namespace glm;

class RasterizationEngine : public IRenderingEngine
{
private:
    Mesh mesh;
    Texture text;
    GLShader shader;
    Camera camera = Camera(640, 480, vec3(0.0f, 0.0f, 2.0f));
    GLuint VAO, VBO;

public:
    ~RasterizationEngine() override;
    void Initialize(const RenderingEngineInfo &renderingEngineInfo) final;
    void Release() final;
    void Render(float lag) final;
    void Draw(GLFWwindow *window);
};