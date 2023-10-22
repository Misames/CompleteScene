#pragma once

#include <tiny_obj_loader.hpp>
#include "Vertex.hpp"
#include "IComponent.hpp"

using namespace std;
using namespace tinyobj;

struct Mesh : IComponent
{
    uint32_t indexVertex;
    attrib_t attribs;
    vector<Vertex> vertexs;
    vector<shape_t> shapes;
    vector<material_t> materials;

    ~Mesh() override;
    void Initialize() final;
    void Release() final;
    void Update() final;
    bool LoadMesh(const char *path);
};