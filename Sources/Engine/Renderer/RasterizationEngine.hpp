#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "IRenderingEngine.hpp"
#include "../../Tools/GLShader.hpp"
#include "../../Engine/Core/Camera.hpp"

class RasterizationEngine : public IRenderingEngine
{
private:
    GLShader shader;
    Camera camera = Camera(640, 480, glm::vec3(0.0f, 0.0f, 2.0f));

public:
    ~RasterizationEngine() override;
    void Initialize(const RenderingEngineInfo &renderingEngineInfo) final;
    void Release() final;
    void Render(float lag) final;
    void Draw(GLFWwindow *window);
    void GenerateTexture() const;
};