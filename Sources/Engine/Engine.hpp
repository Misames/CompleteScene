#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer/IRenderingEngine.hpp"
#include "Renderer/RasterizationEngine.hpp"

using namespace std;

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