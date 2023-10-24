#pragma once

#include "Renderer/IRenderingEngine.hpp"
#include "Renderer/RasterizationEngine.hpp"

struct EngineInfo
{
    RenderingEngineInfo *renderingEngineInfo;
};

class Engine
{
private:
    bool initialized = false;
    IRenderingEngine *renderingEngine = nullptr;

public:
    ~Engine();
    void Initialize(const EngineInfo &);
    void Release();
    void Run();
};