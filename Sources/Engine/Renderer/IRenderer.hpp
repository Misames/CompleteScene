#pragma once

#include "IWindow.hpp"

enum RendererType
{
    OPENGL,
    VULKAN,
    DIRECTX
};

struct RendererInfo
{
    RendererType rendererType;
    WindowInfo *windowInfo;
};

class IRenderer
{
protected:
    bool initialized = false;
    IWindow *window = nullptr;

public:
    virtual ~IRenderer() = default;
    virtual void Initialize(const RendererInfo &rendererInfo) = 0;
    virtual void Release() = 0;
    IWindow *GetWindow() const;
};