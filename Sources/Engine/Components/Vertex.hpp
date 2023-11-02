#pragma once

#include <glm/glm.hpp>

using namespace glm;

class Vertex
{
public:
    vec3 position;
    vec3 normal;
    vec2 uv;
    vec4 tangent;
    uint8_t color[4];

    static constexpr float EPSILON = 0.001f;

    static inline bool IsSame(const vec2 &lhs, const vec2 &rhs)
    {
        if (fabsf(lhs.x - rhs.x) < EPSILON && fabsf(lhs.y - rhs.y) < EPSILON)
            return true;
        return false;
    }

    static inline bool IsSame(const vec3 &lhs, const vec3 &rhs)
    {
        if (fabsf(lhs.x - rhs.x) < EPSILON && fabsf(lhs.y - rhs.y) < EPSILON && fabsf(lhs.z - rhs.z) < EPSILON)
            return true;
        return false;
    }

    inline bool IsSame(const Vertex &v) const
    {
        if (IsSame(position, v.position) && IsSame(normal, v.normal) && IsSame(uv, v.uv))
            return true;
        return false;
    }
};
