#include "astScripter_image.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
bool astScripter_image::init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0)
    {
        utils::printError("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(-1);
    }
    if (TTF_Init() < 0)
    {
        utils::printError("can't initialize SDL TTF\n");
        exit(-1);
    }
    screen_bpp = 32;
    screen_height = 1280;
    screen_width = 800;
    screen_device_width = screen_width;
    screen_device_height = screen_height;
    window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_SWSURFACE);
    screen_surface = SDL_GetWindowSurface(window);
    texture_format = SDL_PIXELFORMAT_ARGB8888;
    if (screen_surface == nullptr)
    {
        printError("cannot init surface");
    }
    dirty_rect.setDimension(screen_width, screen_height);
    screen_rect.x = screen_rect.y = 0;
    screen_rect.w = screen_width;
    screen_rect.h = screen_height;
}
SDL_Surface *astScripter_image::createRectangleSurface(string filename, bool *has_alpha, unsigned char *alpha)
{
    int c = 1, w = 0, h = 0;
    bool decimal_flag = false;
    while (filename[c] != 0x0a && filename[c] != 0x00)
    {
        if (!decimal_flag && filename[c] >= '0' && filename[c] <= '9')
            w = w * 10 + filename[c] - '0';
        if (filename[c] == '.')
            decimal_flag = true;
        if (filename[c] == ',')
        {
            c++;
            break;
        }
        c++;
    }

    decimal_flag = false;
    while (filename[c] != 0x0a && filename[c] != 0x00)
    {
        if (!decimal_flag && filename[c] >= '0' && filename[c] <= '9')
            h = h * 10 + filename[c] - '0';
        if (filename[c] == '.')
            decimal_flag = true;
        if (filename[c] == ',')
        {
            c++;
            break;
        }
        c++;
    }

    while (filename[c] == ' ' || filename[c] == '\t')
        c++;
    int n = 0, c2 = c;
    while (filename[c] == '#')
    {
        uchar3 col;
        readColor(&col, filename.c_str() + c);
        n++;
        c += 7;
        while (filename[c] == ' ' || filename[c] == '\t')
            c++;
    }

    SDL_PixelFormat *fmt = image_surface->format;
    SDL_Surface *tmp = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h,
                                            fmt->BitsPerPixel, fmt->Rmask, fmt->Gmask, fmt->Bmask, fmt->Amask);

    c = c2;
    for (int i = 0; i < n; i++)
    {
        uchar3 col;
        readColor(&col, filename.c_str() + c);
        c += 7;
        while (filename[c] == ' ' || filename[c] == '\t')
            c++;

        SDL_Rect rect;
        rect.x = w * i / n;
        rect.y = 0;
        rect.w = w * (i + 1) / n - rect.x;
        if (i == n - 1)
            rect.w = w - rect.x;
        rect.h = h;
        SDL_FillRect(tmp, &rect, SDL_MapRGBA(tmp->format, col[0], col[1], col[2], alpha ? *alpha : 0xff));
    }

    if (has_alpha)
    {
        if (fmt->Amask)
            *has_alpha = true;
        else
            *has_alpha = false;
    }

    return tmp;
}
SDL_Surface *astScripter_image::createSurfaceFromFile(string filename, bool *has_alpha, int *location)
{
    int len;
    char *buf;
    getFile(filename.c_str(), buf, len);
    num_loaded_images++;
    mean_size_of_loaded_images += len;
    SDL_RWops *src = SDL_RWFromMem(buf, len);
    int is_png = IMG_isPNG(src);
    SDL_Surface *tmp = IMG_Load_RW(src, 0);
    if (tmp && has_alpha)
    {
        if (tmp->format->Amask || is_png)
        {
            *has_alpha = true;
        }
        else
        {
            *has_alpha = false;
        }
    }
    SDL_RWclose(src);
    free(buf);
    if (!tmp)
    {
        printf("can not load file [%s]", filename.c_str());
    }
    return tmp;
}
SDL_Surface *astScripter_image::loadImage(string file)
{
    if (file.empty())
    {
        return nullptr;
    }
    SDL_Surface *tmp = nullptr;
    tmp = createSurfaceFromFile(file, nullptr, nullptr);
    SDL_Surface *ret;
    if ((tmp->w * tmp->format->BytesPerPixel == tmp->pitch) &&
        (tmp->format->BitsPerPixel == image_surface->format->BitsPerPixel) &&
        (tmp->format->Rmask == image_surface->format->Rmask) &&
        (tmp->format->Gmask == image_surface->format->Gmask) &&
        (tmp->format->Bmask == image_surface->format->Bmask) &&
        (tmp->format->Amask == image_surface->format->Amask))
    {
        ret = tmp;
    }
    else
    {
        ret = SDL_ConvertSurface(tmp, image_surface->format, SDL_SWSURFACE);
        SDL_FreeSurface(tmp);
    }
    return ret;
}
void astScripter_image::refreshSurface(SDL_Surface *surface, SDL_Rect *clip_src, int refresh_mode)
{
    SDL_Rect clip;
    clip.x = clip.y = 0;
    clip.w = surface->w;
    clip.h = surface->h;
}