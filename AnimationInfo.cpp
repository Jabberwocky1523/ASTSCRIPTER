#include "AnimationInfo.h"
AnimationInfo::AnimationInfo()
{
    image_surface = nullptr;
}
AnimationInfo::AnimationInfo(const AnimationInfo &anim)
{
    *this = anim;
}
AnimationInfo &AnimationInfo::operator=(const AnimationInfo &anim)
{
    if (this != &anim)
    {
        memcpy(this, &anim, sizeof(AnimationInfo));
        if (image_surface)
        {
            image_surface = allocSurface(anim.image_surface->w, anim.image_surface->h, texture_format);
            memcpy(image_surface->pixels, anim.image_surface->pixels, anim.image_surface->pitch * anim.image_surface->h);
        }
    }
    return *this;
}
SDL_Surface *AnimationInfo::allocSurface(int w, int h, Uint32 texture_format)
{
    SDL_Surface *surface;
    if (texture_format == SDL_PIXELFORMAT_RGB565)
        surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 16, 0xf800, 0x07e0, 0x001f, 0);
    else if (texture_format == SDL_PIXELFORMAT_ABGR8888)
        surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
    else // texture_format == SDL_PIXELFORMAT_ARGB8888
        surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    return surface;
}
SDL_Surface *AnimationInfo::alloc32bitSurface(int w, int h, Uint32 texture_format)
{
    if (texture_format == SDL_PIXELFORMAT_RGB565)
        return allocSurface(w, h, SDL_PIXELFORMAT_ARGB8888);
    else
        return allocSurface(w, h, texture_format);
}
int AnimationInfo::doClipping(SDL_Rect *dst, SDL_Rect *clip, SDL_Rect *clipped)
{
    if (clipped)
        clipped->x = clipped->y = 0;

    if (!dst ||
        dst->x >= clip->x + clip->w || dst->x + dst->w <= clip->x ||
        dst->y >= clip->y + clip->h || dst->y + dst->h <= clip->y)
        return -1;

    if (dst->x < clip->x)
    {
        dst->w -= clip->x - dst->x;
        if (clipped)
            clipped->x = clip->x - dst->x;
        dst->x = clip->x;
    }
    if (clip->x + clip->w < dst->x + dst->w)
    {
        dst->w = clip->x + clip->w - dst->x;
    }

    if (dst->y < clip->y)
    {
        dst->h -= clip->y - dst->y;
        if (clipped)
            clipped->y = clip->y - dst->y;
        dst->y = clip->y;
    }
    if (clip->y + clip->h < dst->y + dst->h)
    {
        dst->h = clip->y + clip->h - dst->y;
    }
    if (clipped)
    {
        clipped->w = dst->w;
        clipped->h = dst->h;
    }

    return 0;
}