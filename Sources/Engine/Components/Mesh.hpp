#pragma once

#include <vector>

using namespace std;

struct Mesh
{
    vector<float> vertex;
    uint32_t indexVertex = 0;

    Mesh();
    ~Mesh();
    bool LoadMesh(const char *path);
    vector<float> GetVertices() const;
};