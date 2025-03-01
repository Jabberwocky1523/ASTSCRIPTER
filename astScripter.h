#ifndef AST_SCRIPTER_H
#define AST_SCRIPTER_H
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "astScripter_image.h"
#include "DirectDraw.h"
#include "DirtyRect.h"
#include "string"
class ast_Scripter
{
public:
    DirectDraw directdraw;
    bool init();
    // ----------------------------------------
    // variables and methods relevant to image
    astScripter_image ast_image;
    void flush(SDL_Rect *rect, bool direct_flag);
    void flushDirect(SDL_Rect &rect);
};
#endif