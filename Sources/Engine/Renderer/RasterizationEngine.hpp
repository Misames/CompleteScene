#pragma once

#include "../Components/Scene.hpp"
#include "IRenderingEngine.hpp"

class RasterizationEngine : public IRenderingEngine
{
private:
    Scene *scene = nullptr;

public:
    ~RasterizationEngine() override;
    void Initialize(const RenderingEngineInfo &renderingEngineInfo) final;
    void Release() final;
    void Render(float lag) final;
};