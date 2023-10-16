#pragma once

#include "IRenderer.hpp"

enum RenderingEngineType
{
    RASTERIZATION,
    RAY_TRACING_CPU,
    RAY_TRACING_GPU
};

struct RenderingEngineInfo
{
    RenderingEngineType renderingEngineType;
    RendererInfo *rendererInfo;
};

class IRenderingEngine
{
protected:
    bool initialized = false;
    IRenderer *renderer = nullptr;

public:
    virtual ~IRenderingEngine() = default;
    virtual void Initialize(const RenderingEngineInfo &renderingEngineInfo) = 0;
    virtual void Release() = 0;
    virtual void Render(float lag) = 0;
    IRenderer *GetRenderer() const;
};