#include "DirtyRect.h"
void DirtyRect::setDimension(int w, int h)
{
    screen_height = h;
    screen_width = w;
}
void DirtyRect::add(SDL_Rect src)
{
    if (src.w == 0 || src.h == 0)
        return;

    if (src.x < 0)
    {
        if (src.w < -src.x)
            return;
        src.w += src.x;
        src.x = 0;
    }
    if (src.y < 0)
    {
        if (src.h < -src.y)
            return;
        src.h += src.y;
        src.y = 0;
    }
    if (src.x >= screen_width)
        return;
    if (src.x + src.w >= screen_width)
        src.w = screen_width - src.x;

    if (src.y >= screen_height)
        return;
    if (src.y + src.h >= screen_height)
        src.h = screen_height - src.y;
    bounding_box = calBoundingBox(bounding_box, src);
}
SDL_Rect DirtyRect::calBoundingBox(SDL_Rect src1, SDL_Rect &src2)
{
    if (src2.w == 0 || src2.h == 0)
    {
        return src1;
    }
    if (src1.w == 0 || src1.h == 0)
    {
        return src2;
    }

    if (src1.x > src2.x)
    {
        src1.w += src1.x - src2.x;
        src1.x = src2.x;
    }
    if (src1.y > src2.y)
    {
        src1.h += src1.y - src2.y;
        src1.y = src2.y;
    }
    if (src1.x + src1.w < src2.x + src2.w)
    {
        src1.w = src2.x + src2.w - src1.x;
    }
    if (src1.y + src1.h < src2.y + src2.h)
    {
        src1.h = src2.y + src2.h - src1.y;
    }

    return src1;
}
void DirtyRect::clear()
{
    bounding_box.w = bounding_box.h = 0;
}
void DirtyRect::fill(int w, int h)
{
    bounding_box.x = bounding_box.y = 0;
    bounding_box.w = w;
    bounding_box.h = h;
}