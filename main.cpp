#include "tgaimage.h"
#include "line.h"
#include "model.h"
#include <vector>
#include "geometry.h"
#include "triangle.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const int width = 800;
const int height = 800;
Model* model = nullptr;
float* zbuffer = nullptr;

int main(int argc, char** argv)
{
    TGAImage image(width, height, TGAImage::RGB);
    zbuffer = new float[width * height];

    for(int i = width * height - 1; i >=0; i--)
    {
        zbuffer[i] = -std::numeric_limits<float>::max();
    }

    if(argc > 1)
    {
        model = new Model(argv[1]);
    } 
    else
    {
        model = new Model("obj/african_head.obj");
    }

    Vec3f light_dir(0, 0, -1);
    for(int faceIndex = 0; faceIndex < model->nfaces(); faceIndex++)
    {
        std::vector<int> face = model->face(faceIndex);
        Vec3f screen_coords[3];
        Vec3f world_coords[3];
        for(int i = 0; i < 3; ++i)
        {
            Vec3f world_coord= model->vert(face[i]);
            screen_coords[i] = Vec3f(int((world_coord.x + 1.0f) * width / 2.0f + 0.5), int((world_coord.y + 1.0f) * height / 2.0f + 0.5), world_coord.z);
            world_coords[i] = world_coord;
        }

        // cross
        Vec3f n = cross(world_coords[2] - world_coords[0], world_coords[1] - world_coords[0]);
        n.normalize();
        float intensity = n * light_dir;
        if(intensity > 0)
        {
            triangleBoundingbox(screen_coords, zbuffer, image, TGAColor(intensity * 255, intensity * 255, intensity * 255, 255));
        }
    } 
    image.flip_vertically();
    image.write_tga_file("output.tga");
    delete model;
    model = nullptr;
    delete zbuffer;
    zbuffer = nullptr;
    return 0;
}