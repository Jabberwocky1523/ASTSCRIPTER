#ifndef AST_IMAGE_H
#define AST_IMAGE_H
#include "SDL.h"
#include "string"
class astScripter_image
{
public:
    bool init();
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
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

    void loadImage(std::string file);
};
#endif