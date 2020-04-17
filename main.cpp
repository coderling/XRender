#include "tgaimage.h"
#include "line.h"
#include "model.h"
#include <vector>
#include "geometry.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const int width = 800;
const int height = 800;
Model *model = nullptr;

int main(int argc, char** argv)
{
    if(2 == argc)
    {
        model = new Model(argv[1]);
    }
    else
    {
        model = new Model("obj/african_head.obj");
    }

    TGAImage image(width, height, TGAImage::RGB);
    for(int faceIndex = 0; faceIndex < model->nfaces(); faceIndex++)
    {
        std::vector<int> face = model->face(faceIndex);
        for(int i = 0; i < 3; i++)
        {
            Vec3f v0 = model->vert(face[i]);
            Vec3f v1 = model->vert(face[(i+1) % 3]);
            int x0 = (v0.x + 1.0f) * width / 2.0f;
            int y0 = (v0.y + 1.0f) * height / 2.0f;
            int x1 = (v1.x + 1.0f) * width / 2.0f;
            int y1 = (v1.y + 1.0f) * height / 2.0f;
            line(x0, y0, x1, y1, image, white);
        }
    }
    
    image.flip_vertically();
    image.write_tga_file("output.tga");
    delete model;
    return 0;
}