
#ifndef AST_BUTTON_H__
#define SAT_BUTTON_H__
#include "SDL.h"
struct ButtonLink
{
    enum
    {
        NORMAL_BUTTON = 0,
        SPRITE_BUTTON = 1,
        LOOKBACK_BUTTON = 2,
        TMP_SPRITE_BUTTON = 3
    };

    ButtonLink *next;
    int button_type;
    int no;
    int sprite_no;
    char *exbtn_ctl[3];
    SDL_Rect select_rect;
    SDL_Rect image_rect;
    // AnimationInfo *anim[2];
    int show_flag; // 0...show nothing, 1... show anim[0], 2 ... show anim[1]

    ButtonLink()
    {
        button_type = NORMAL_BUTTON;
        next = NULL;
        exbtn_ctl[0] = exbtn_ctl[1] = exbtn_ctl[2] = NULL;
        // anim[0] = anim[1] = NULL;
        show_flag = 0;
    };

    ~ButtonLink()
    {
        for (int i = 0; i < 3; i++)
            if (exbtn_ctl[i])
                delete[] exbtn_ctl[i];
    };

    void insert(ButtonLink *button)
    {
        button->next = this->next;
        this->next = button;
    };

    void removeSprite(int no)
    {
        ButtonLink *bl = this;
        while (bl->next)
        {
            if (bl->next->sprite_no == no &&
                bl->next->button_type == SPRITE_BUTTON)
            {
                ButtonLink *bl2 = bl->next;
                bl->next = bl->next->next;
                delete bl2;
            }
            else
            {
                bl = bl->next;
            }
        }
    };
};

#endif // __BUTTON_LINK_H__
