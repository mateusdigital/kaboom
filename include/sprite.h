#ifndef __Game_Kaboom_include_sprite_h__
#define __Game_Kaboom_include_sprite_h__

/* SDL */
#include <SDL2/SDL.h>


/*******************************************************************************
*                                                                              *
*******************************************************************************/
typedef struct _sprite_t
{
    int x, y;
    int w, h;

    SDL_Texture *texture;

} sprite_t;


/*******************************************************************************
*                                                                              *
*******************************************************************************/
void sprite_init(sprite_t *sprite,
                 int texture_id,
                 int frame_w, int frame_h,
                 int frame_x, int frame_y);

void sprite_draw(sprite_t *sprite, int x, int y);

#endif /* __Game_Kaboom_include_sprite_h__ */
