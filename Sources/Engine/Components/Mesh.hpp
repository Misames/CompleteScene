#pragma once

#include <vector>
#include <stdint.h>
#include "Vertex.hpp"

using namespace std;

struct Mesh
{
    uint32_t indexVertex;
    vector<Vertex> vertexs;

    Mesh();
    ~Mesh();
    bool LoadMesh(const char *path);
};