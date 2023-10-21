#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.hpp>

#include <iostream>
#include "Mesh.hpp"

using namespace tinyobj;

Mesh::Mesh()
{
    vertexs = vector<Vertex>();
    indexVertex = 0;
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
        cout << "Mesh not load" << endl;
        cout << warm << err << endl;
        return false;
    }

    for (auto &shape : shapes)
    {
        Vertex currentVertex;
        uint32_t indexOffset = 0;

        uint32_t fvSize = shape.mesh.num_face_vertices.size();
        for (uint32_t i = 0; i < fvSize; ++i)
        {
            uint32_t fv = shape.mesh.num_face_vertices[i];
            for (uint32_t j = 0; j < fv; ++j)
            {
                index_t idx = shape.mesh.indices[indexOffset + j];

                currentVertex.position.x = attribs.vertices[3 * idx.vertex_index + 0];
                currentVertex.position.y = attribs.vertices[3 * idx.vertex_index + 1];
                currentVertex.position.z = attribs.vertices[3 * idx.vertex_index + 2];

                if (!attribs.normals.empty())
                {
                    currentVertex.normal.x = attribs.normals[3 * idx.normal_index + 0];
                    currentVertex.normal.y = attribs.normals[3 * idx.normal_index + 1];
                    currentVertex.normal.z = attribs.normals[3 * idx.normal_index + 2];
                }

                if (!attribs.texcoords.empty())
                {
                    currentVertex.uv.x = attribs.texcoords[2 * idx.texcoord_index + 0];
                    currentVertex.uv.y = attribs.texcoords[2 * idx.texcoord_index + 1];
                }

                vertexs.push_back(currentVertex);
            }

            indexOffset += fv;
            indexVertex += fv;
        }
    }

    cout << "Mesh load" << endl;
    return true;
}
