
#pragma once

#include <tgaimage.h>
#include "geometry.h"

void line(int x0, int y0, int x1, int y1, TGAImage &image, const TGAColor &color);
void line(Vec2i t1, Vec2i t2, TGAImage &image, const TGAColor &color);