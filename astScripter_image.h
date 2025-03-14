#ifndef AST_IMAGE_H
#define AST_IMAGE_H
#include "SDL.h"
#include "string"
#include "Util.hpp"
#include "DirtyRect.h"
#include "AnimationInfo.h"
class astScripter_image : public utils
{
    /* Global definitions  */
public:
    int screen_ratio1, screen_ratio2;
    int screen_width, screen_height;
    int screen_device_width, screen_device_height;
    int device_width, device_height;
    float screen_scale_ratio1, screen_scale_ratio2;
    SDL_Rect screen_rect;
    SDL_Rect render_view_rect;

public:
    // ----------------------------------------
    // variables and methods relevant to animation
    AnimationInfo bg_info;

public:
    using string = std::string;
    typedef unsigned char uchar3[3];
    bool initSDL();
    bool init();
    enum
    {
        REFRESH_NONE_MODE = 0,
        REFRESH_NORMAL_MODE = 1,
        REFRESH_SAYA_MODE = 2,
        REFRESH_SHADOW_MODE = 4,
        REFRESH_TEXT_MODE = 8,
        REFRESH_CURSOR_MODE = 16
    };
    DirtyRect dirty_rect;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    Uint32 texture_format;
    void setCaption(const char *title, const char *iconstr = nullptr);
    SDL_Surface *accumulation_surface; // Final image, i.e. picture_surface (+ shadow + text_surface)
    SDL_Surface *backup_surface;       // Final image w/o (shadow + text_surface) used in leaveTextDisplayMode()
    SDL_Surface *screen_surface;       // Text + Select_image + Tachi image + background
    SDL_Surface *effect_dst_surface;   // Intermediate source buffer for effect
    SDL_Surface *effect_src_surface;   // Intermediate destnation buffer for effect
    SDL_Surface *effect_tmp_surface;   // Intermediate buffer for effect
    SDL_Surface *screenshot_surface;   // Screenshot
    int screenshot_w, screenshot_h;
    SDL_Surface *image_surface;
    int max_texture_width, max_texture_height;
    SDL_Texture *blt_texture;
    SDL_Rect blt_texture_src_rect;
    unsigned char *tmp_image_buf;
    unsigned long tmp_image_buf_length;
    unsigned long mean_size_of_loaded_images;
    unsigned long num_loaded_images;
    unsigned char *resize_buffer;
    size_t resize_buffer_size;

    SDL_Surface *loadImage(string file);
    SDL_Surface *createRectangleSurface(string filename, bool *has_alpha, unsigned char *alpha = NULL);
    SDL_Surface *createSurfaceFromFile(string filename, bool *has_alpha, int *location);
    int resizeSurface(SDL_Surface *src, SDL_Surface *dst);
    void alphaBlend(SDL_Surface *mask_surface, int trans_mode, Uint32 mask_value = 255, SDL_Rect *clip = NULL,
                    SDL_Surface *src1 = NULL, SDL_Surface *src2 = NULL, SDL_Surface *dst = NULL);
    void alphaBlendText(SDL_Surface *dst_surface, SDL_Rect dst_rect,
                        SDL_Surface *src_surface, SDL_Color &color, SDL_Rect *clip, bool rotate_flag);
    void makeNegaSurface(SDL_Surface *surface, SDL_Rect &clip);
    void makeMonochromeSurface(SDL_Surface *surface, SDL_Rect &clip);
    void refreshSurface(SDL_Surface *surface, SDL_Rect *clip_src, int refresh_mode = REFRESH_NORMAL_MODE);
    void refreshSprite(int sprite_no, bool active_flag, int cell_no, SDL_Rect *check_src_rect, SDL_Rect *check_dst_rect);
    void createBackground();
    void refresh(SDL_Rect &clip_src);
};
#endif