#include "tgaimage.h"
#include "line.h"
#include "model.h"
#include <vector>
#include "geometry.h"
#include "triangle.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const int width = 200;
const int height = 200;
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
    Vec2i pts[3] = {Vec2i(10,10), Vec2i(100, 30), Vec2i(190, 160)}; 
    triangleBoundingbox(pts, image, red)
    image.flip_vertically();
    image.write_tga_file("output.tga");
    delete model;
    return 0;
}