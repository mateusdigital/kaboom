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
sprite_t sprite_load  (int texture_id);
sprite_t sprite_unload(int texture_id);

void sprite_draw(sprite_t *sprite);

#endif /* __Game_Kaboom_include_sprite_h__ */
