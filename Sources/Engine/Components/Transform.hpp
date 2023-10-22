#pragma once

#include "IComponent.hpp"

class Transform : IComponent
{
private:
    int32_t tx, ty, tz;
    int32_t rx, ry, rz;
    int32_t sx, sy, sz;
};