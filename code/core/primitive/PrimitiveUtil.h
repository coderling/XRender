
#include <SDL.h>

#include "XPoint.h"
#include "../../app/XApp.h"

void DrawPoint(const XPoint& p);

void DrawPoints(XPoint const *pArr, int size);

void DrawLineDDA(const XPoint& st, const XPoint& ed);