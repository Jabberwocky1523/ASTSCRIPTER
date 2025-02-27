#ifndef AST_DIRTY_RECT_H
#define AST_DIRTY_RECT_H
#include "SDL.h"
class DirtyRect
{
public:
    SDL_Rect bounding_box;
    int screen_width, screen_height;
    DirtyRect()
    {
        screen_height = screen_width = 0;
        bounding_box.w = bounding_box.h = 0;
    }
    DirtyRect(const DirtyRect &d)
    {
        screen_height = d.screen_height;
        screen_width = d.screen_width;
        bounding_box = d.bounding_box;
    };
    ~DirtyRect() = default;
    DirtyRect &operator=(const DirtyRect &d)
    {
        screen_height = d.screen_height;
        screen_width = d.screen_width;
        bounding_box = d.bounding_box;
        return *this;
    };
    void setDimension(int w, int h);
    void add(SDL_Rect src);
    void clear();
    void fill(int w, int h);
    SDL_Rect calBoundingBox(SDL_Rect src1, SDL_Rect &src2);
};
#endif