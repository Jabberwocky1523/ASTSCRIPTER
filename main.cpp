#include "astScripter.h"
int main()
{
    ast_Scripter s;
    s.init();
    SDL_Rect rect;
    rect.h = 480;
    rect.w = 640;
    rect.x = rect.y = 0;
    SDL_Event event;
    s.ast_image.bg_info.image_surface = s.ast_image.loadImage("../zy.jpg");
    s.flush(&rect, false);
    rect.x = 100;
    rect.y = 0;
    s.ast_image.bg_info.image_surface = s.ast_image.loadImage("../bg001.jpg");
    s.flush(&rect, true);
    while (true)
    {
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                return -1;
            }
        }
    }
}