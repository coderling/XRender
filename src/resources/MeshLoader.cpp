#include <iostream>

#include "MeshLoader.h"

XRender::Res::ILoader<XRender::Mesh>::ILoader()
{
    auto obj_loader = std::bind(&ILoader<Mesh>::ObjFileLoad, this, std::placeholders::_1, std::placeholders::_2);
    meshLoaders.emplace("obj", obj_loader);
}

std::unique_ptr<XRender::Mesh> XRender::Res::ILoader<XRender::Mesh>::Load(const std::string& path)
{
    std::unique_ptr<XRender::Mesh> ret = std::make_unique<XRender::Mesh>();
    std::string ext = XRender::Res::FileExtendName(path);
    auto iter = meshLoaders.find(ext);
    if(iter != meshLoaders.end())
    {
        iter->second(ret.get(), path);
    }

    return ret;
}

void XRender::Res::ILoader<XRender::Mesh>::Unload(std::unique_ptr<XRender::Mesh> res)
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
    std::vector<Vec3i> normals;
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
            
            mesh->positions.emplace_back(v);
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

    mesh->vertex_count = indeies.size();
    mesh->uv.emplace(std::vector<Vec2f>());
    mesh->normals.emplace(std::vector<Vec3f>());
    for(uint32_t t = 0; t < indeies.size(); ++t)
    {
        mesh->indeies.emplace_back(indeies[t][0]);
        mesh->uv->emplace_back(uvs[indeies[t][1]]);
        mesh->normals->emplace_back(normals[indeies[t][2]]);
    }
}