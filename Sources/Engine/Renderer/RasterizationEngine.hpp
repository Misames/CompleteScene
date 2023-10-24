#pragma once

#include <iostream>
#include "IRenderingEngine.hpp"
#include "OpenGL/OpenGLRenderer.hpp"
#include "../Components/Scene.hpp"

using namespace std;

class RasterizationEngine : public IRenderingEngine
{
private:
    Scene *scene;

public:
    ~RasterizationEngine() override;
    void Initialize(const RenderingEngineInfo &renderingEngineInfo) final;
    void Release() final;
    void Render(float lag) final;
};