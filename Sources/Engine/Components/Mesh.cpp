#define TINYOBJLOADER_IMPLEMENTATION

#include "Vertex.hpp"

#include "Mesh.hpp"

Mesh::~Mesh()
{
    Release();
}

void Mesh::Initialize()
{
    if (initialized)
        Release();

    vertexs = vector<Vertex>();
    indexVertex = 0;

    initialized = true;
    cout << "Mesh initialize" << endl;
}

void Mesh::Release()
{
    if (initialized)
    {
        initialized = false;
        cout << "Mesh release" << endl;
    }
}

void Mesh::Update() {}

bool Mesh::LoadMesh(const char *meshPath)
{
    string warm, err;
    string mtlPath = meshPath;

    size_t off = mtlPath.rfind("/");
    if (off != string::npos)
        mtlPath.resize(off);
    else
        mtlPath = meshPath;

    bool ret = LoadObj(&attribs, &shapes, &materials, &warm, &err, meshPath, mtlPath.c_str(), true, false);
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

        size_t fvSize = shape.mesh.num_face_vertices.size();
        for (uint32_t i = 0; i < fvSize; ++i)
        {
            uint8_t fv = shape.mesh.num_face_vertices[i];
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
