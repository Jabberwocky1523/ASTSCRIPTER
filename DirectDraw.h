#ifndef AST_DIRECTDRAW_H
#define AST_DIRECTDRAW_H
#include "SDL.h"
#define MAX_TEXTURE_NUM 16
class DirectDraw
{
public:
    SDL_Texture *texture_info[MAX_TEXTURE_NUM] = {0};
    bool loadTexture(int no, const char *file);
    bool deleteTexture(int no);
    bool draw(int no, int dx, int dy, int w, int h, int sx, int sy, int alpha = 255, bool add = false);
    bool fill(int lx, int ly, int rx, int ry, int r, int g, int b);
    bool getTextureSize(int no, int &w, int &h);
    bool present();
    bool clear();
};
#endif