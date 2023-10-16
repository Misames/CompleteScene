#pragma once

#include "Renderer/IRenderingEngine.hpp"

struct EngineInfo
{
    RenderingEngineInfo *renderingEngineInfo;
};

class Engine
{
private:
    bool initialize = false;
    IRenderingEngine *renderingEngine = nullptr;

public:
    ~Engine();
    void Initialize(const EngineInfo &);
    void Release();
    void Run();
};