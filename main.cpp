#include "tgaimage.h"
#include "line.h"
#include "model.h"
#include <vector>
#include "geometry.h"
#include "triangle.h"
#include "MVP.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const int width = 800;
const int height = 800;
Model* model = nullptr;
float* zbuffer = nullptr;
const Vec3f vec3f_one = Vec3f(1, 1, 1);
const Vec3f vec3f_zero = Vec3f(0, 0, 0);

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
    Matrix modelM = ModelMatrix(Vec3f(0, 0, -2.f), vec3f_one, Vec3f(0, 15, 0));
    Matrix viewM = CameraViewMatrixByLookAt(vec3f_zero, Vec3f(0, 1, 0), Vec3f(0, 0, -1));
    Matrix projM = PerspectiveProjectionMatrix(60.f, width * 1.0f / height, 0.1f, 100.f);
    Matrix viewPortM = ViewPortMatrix(0, 0, width, height);
    for(int faceIndex = 0; faceIndex < model->nfaces(); faceIndex++)
    {
        std::vector<int> face = model->face(faceIndex);
        Vec3f screen_coords[3];
        Vec3f world_coords[3];
		Vec2f tex_coords[3];
        for(int i = 0; i < 3; ++i)
        {
            Vec3f v = model->vert(face[i]);
			Vec4f v4 = embed<4>(v);
            Vec4f world_coord= modelM * v4;
            Vec4f spos = projM * viewM * world_coord;
			spos[0] /= spos[3]; spos[1] /= spos[3]; spos[2] /= spos[3]; spos[3] = 1;
			spos = viewPortM * spos;
			screen_coords[i] = embed<3>(spos);
			world_coords[i] = embed<3>(world_coord);
			tex_coords[i] = model->uv(faceIndex, i);
        }

        // cross
        Vec3f n = cross(world_coords[2] - world_coords[0], world_coords[1] - world_coords[0]);
        n.normalize();
        float intensity = n * light_dir;
        if(intensity > 0)
        {
            triangleBoundingbox(model, screen_coords, tex_coords, zbuffer, image);
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