#pragma once

class RenderContext
{
protected:
    int width = 400;
    int height = 400;
public:
    virtual ~RenderContext();
    virtual void Init(int w, int h) = 0;
    virtual void SetPixel(int x, int y, TGAColor color) = 0;
    virtual void SetDepthBuffer(int x, int y, float v) = 0;
    virtual float GetDepthBuffer(int x, int y) = 0;
};