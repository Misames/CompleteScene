#pragma once

#include <iostream>
#include <tiny_obj_loader.hpp>
#include "IComponent.hpp"
#include "Vertex.hpp"

using namespace std;
using namespace tinyobj;

class Mesh : IComponent
{
private:
    uint32_t indexVertex;
    attrib_t attribs;
    vector<shape_t> shapes;
    vector<material_t> materials;

public:
    vector<Vertex> vertexs;

    ~Mesh() override;

    void Initialize() final;
    void Release() final;
    void Update() final;

    bool LoadMesh(const char *path);
};