#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.hpp>

#include <iostream>
#include <stdint.h>
#include "Mesh.hpp"

using namespace tinyobj;

Mesh::Mesh()
{
    vertex = vector<float>();
    cout << "Mesh initialize" << endl;
}

Mesh::~Mesh()
{
    cout << "Mesh release" << endl;
}

bool Mesh::LoadMesh(const char *path)
{
    string warm, err;
    attrib_t attribs;
    vector<shape_t> shapes;
    vector<material_t> materials;

    bool ret = LoadObj(&attribs, &shapes, &materials, &warm, &err, path, "", true, false);
    if (!ret)
    {
        cout << "Cube not load" << endl;
        cout << warm << err << endl;
        return false;
    }

    for (auto &shape : shapes)
    {
        int indexOffset = 0;
        uint32_t fvSize = shape.mesh.num_face_vertices.size();
        for (int j = 0; j < fvSize; ++j)
        {
            uint32_t fv = shape.mesh.num_face_vertices[j];
            for (uint32_t k = 0; k < fv; ++k)
            {
                index_t idx = shape.mesh.indices[indexOffset + k];
                vertex.push_back(attribs.vertices[3 * idx.vertex_index + 0]);
                vertex.push_back(attribs.vertices[3 * idx.vertex_index + 1]);
                vertex.push_back(attribs.vertices[3 * idx.vertex_index + 2]);

                if (!attribs.normals.empty())
                {
                    vertex.push_back(attribs.normals[3 * idx.normal_index + 0]);
                    vertex.push_back(attribs.normals[3 * idx.normal_index + 1]);
                    vertex.push_back(attribs.normals[3 * idx.normal_index + 2]);
                }

                if (!attribs.texcoords.empty())
                {
                    vertex.push_back(attribs.texcoords[2 * idx.texcoord_index + 0]);
                    vertex.push_back(attribs.texcoords[2 * idx.texcoord_index + 1]);
                }
            }
            indexOffset += fv;
            indexVertex += fv;
        }
    }

    cout << "Cube load" << endl;
    return true;
}

vector<float> Mesh::GetVertices() const
{
    return vertex;
}
