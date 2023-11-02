#include <iostream>
#include "Engine/Engine.hpp"

using namespace std;

int main()
{
    WindowInfo windowInfo{};
    windowInfo.width = 1280;
    windowInfo.height = 720;
    windowInfo.title = "Reve Engine";

    RendererInfo rendererinfo{};
    rendererinfo.rendererType = RendererType::OPENGL;
    rendererinfo.windowInfo = &windowInfo;

    RenderingEngineInfo renderingEngineInfo{};
    renderingEngineInfo.renderingEngineType = RenderingEngineType::RASTERIZATION;
    renderingEngineInfo.rendererInfo = &rendererinfo;

    EngineInfo engineInfo{};
    engineInfo.renderingEngineInfo = &renderingEngineInfo;

    Engine engine;

    try
    {
        engine.Initialize(engineInfo);
        engine.Run();
    }
    catch (const runtime_error &e)
    {
        cerr << e.what() << endl;
    }
    catch (const bad_alloc &e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}