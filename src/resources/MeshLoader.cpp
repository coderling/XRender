#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "ILoader.h"

struct Vec3iHash
{
    std::size_t operator()(const Vec3i& key) const
    {
        using std::hash;
        return (hash<int>()(key.x)) ^ (hash<int>()(key.y)) ^ (hash<int>()(key.z));
    }
};

struct Vec3iEqual
{
    bool operator()(const Vec3i& lhs, const Vec3i& rhs) const
    {
        return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
    }
};

XRender::Res::ILoader<XRender::Mesh>::ILoader()
{
    const auto& obj_loader = std::bind(&ILoader<Mesh>::ObjFileLoad, this, std::placeholders::_1, std::placeholders::_2);
    meshLoaders.emplace("obj", obj_loader);
}

std::unique_ptr<XRender::Mesh> XRender::Res::ILoader<XRender::Mesh>::Load(const std::string& path)
{
    std::string ext = XRender::Res::FileExtendName(path);
    auto iter = meshLoaders.find(ext);
    if(iter != meshLoaders.end())
    {
        std::unique_ptr<XRender::Mesh> ret = std::make_unique<XRender::Mesh>();
        iter->second(ret.get(), path);
        return ret;
    }

    return nullptr;
}

void XRender::Res::ILoader<XRender::Mesh>::UnLoad(std::unique_ptr<XRender::Mesh> res)
{
    
}

void XRender::Res::ILoader<XRender::Mesh>::ObjFileLoad(XRender::Mesh* mesh, const std::string& path)
{
    std::ifstream in;
    in.open(path, std::ifstream::in);
    if(in.fail())
    {
        std::cout << "load obj file fail: " + path << std::endl;
        return;
    }
    std::vector<Vec3f> positions;
    std::vector<Vec3f> normals;
    std::vector<Vec2f> uvs;
    std::vector<Vec3i> indeies;
    std::string line;
    while (!in.eof()) 
    {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if(!line.compare(0, 2, "v "))
        {
            iss >> trash;
            Vec3f v;
            for(int ind = 0; ind < 3; ++ind) iss >> v[ind];
            
            positions.emplace_back(v);
        }
        else if(!line.compare(0, 3, "vn "))
        {
            iss >> trash >> trash;
            Vec3f n;
            for(int ind = 0; ind < 3; ++ind) iss >> n[ind];
            
            normals.emplace_back(n);
        }
        else if(!line.compare(0, 3, "vt "))
        {
            iss >> trash >> trash;
            Vec2f uv;
            for(int ind = 0; ind < 2; ++ind) iss >> uv[ind];

            uvs.emplace_back(uv);
        }
        else if(!line.compare(0, 2, "f "))
        {
            iss >> trash;
            Vec3i index;
            while (iss >> index[0] >> trash >> index[1] >> trash >> index[2]) 
            {
                for(int i = 0; i < 3; i++) index[i]--;

                indeies.emplace_back(index);
            }
        }
    }
    
    std::vector<uint32_t> use_indeies;
    std::vector<Vec3f> use_positions;
    std::vector<Vec2f> use_uv;
    std::vector<Vec3f> use_normals;
    std::unordered_map<Vec3i, uint32_t, Vec3iHash, Vec3iEqual> vertex_indeices;
    for(uint32_t index = 0; index < indeies.size(); ++index)
    {
        const auto& v = indeies[index];
        if (vertex_indeices.count(v) == 1)
        {
            use_indeies.emplace_back(vertex_indeices[v]);
        }
        else
        {
            use_positions.emplace_back(positions[v.x]);
            use_uv.emplace_back(uvs[v.y]);
            use_normals.emplace_back(normals[v.z]);
            uint32_t v_index = use_positions.size() - 1;
            vertex_indeices[v] = v_index;
            use_indeies.emplace_back(v_index);
        }
    }

    mesh->SetPositions(use_positions);
    mesh->SetIndeies(use_indeies);
    mesh->SetUV(use_uv);
    mesh->SetNormals(use_normals);
}