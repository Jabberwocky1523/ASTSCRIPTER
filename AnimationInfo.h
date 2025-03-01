#ifndef ANIMATIONINFO_H
#define ANIMATIONINFO_H
#include "SDL.h"
#include "SDL_image.h"
#include "string.h"
#include "SDL_pixels.h"
typedef unsigned char uchar3[3];
class AnimationInfo
{
public:
    bool visible;
    SDL_Surface *image_surface;
    SDL_Rect bounding_rect;
    Uint32 texture_format;
    AnimationInfo();
    AnimationInfo(const AnimationInfo &anim);
    AnimationInfo &operator=(const AnimationInfo &anim);
    static SDL_Surface *allocSurface(int w, int h, Uint32 texture_format);
    static SDL_Surface *alloc32bitSurface(int w, int h, Uint32 texture_format);
    void allocImage(int w, int h, Uint32 texture_format);
    static int doClipping(SDL_Rect *dst, SDL_Rect *clip, SDL_Rect *clipped = NULL);
};
#endif