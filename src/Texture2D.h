#include "Texture.h"
#include "Color.h"

namespace XRender
{

class Texture2D: public Texture
{
public:
    void Create(const int& width, const int& height);
    void SetPixels(Color* colors);
};

}
