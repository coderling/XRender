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
    Vec2i t1[3] = {Vec2i(10, 70), Vec2i(50, 160), Vec2i(70, 80)};
    Vec2i t2[3] = {Vec2i(180, 50), Vec2i(150, 1), Vec2i(70, 180)};
    Vec2i t3[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)};
    triangle(t1[0], t1[1], t1[2], image, red);    
    triangle(t2[0], t2[1], t2[2], image, red);    
    triangle(t3[0], t3[1], t3[2], image, red);    

    image.flip_vertically();
    image.write_tga_file("output.tga");
    delete model;
    return 0;
}