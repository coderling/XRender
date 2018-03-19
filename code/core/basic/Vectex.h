//顶点数据
#include <SDL.h>

#include "../math/Vector3.h"
class Vectex
{
public:
    Vector3 pos;
    Uint32 color;
    
    Vectex(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
};