#include "astScripter.h"
#include "AnimationInfo.h"
void ast_Scripter::flush(SDL_Rect *rect, bool direct_flag)
{
    if (direct_flag)
        flushDirect(*rect);
    else
    {
        if (rect)
        {
            ast_image.dirty_rect.add(*rect);
        }
        if (ast_image.dirty_rect.bounding_box.w * ast_image.dirty_rect.bounding_box.h > 0)
        {
            flushDirect(ast_image.dirty_rect.bounding_box);
        }
    }
}
void ast_Scripter::flushDirect(SDL_Rect &rect)
{
    ast_image.refresh(rect);
    SDL_Rect dst_rect = rect;
    if (AnimationInfo::doClipping(&dst_rect, &ast_image.screen_rect) || (dst_rect.w == 0 && dst_rect.h == 0))
    {
        return;
    }
    SDL_BlitSurface(ast_image.accumulation_surface, &dst_rect, ast_image.screen_surface, &dst_rect);
    SDL_UpdateWindowSurfaceRects(ast_image.window, &dst_rect, 1);
}
bool ast_Scripter::init()
{
    ast_image.init();
    return true;
}
