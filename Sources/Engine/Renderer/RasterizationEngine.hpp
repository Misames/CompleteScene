#pragma once

#include "IRenderingEngine.hpp"
#include "../Components/Scene.hpp"

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