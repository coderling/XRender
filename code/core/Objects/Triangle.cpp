#include "Triangle.h"

Triangle::Triangle(Vertex& a, Vertex& b, Vertex& c)
{
    m_verteies[0] = a; m_verteies[1] = b; m_verteies[2] = c;
}

const int Triangle::m_indeies[3] = {0, 1, 2};