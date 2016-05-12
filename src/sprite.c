/* Header */
#include "sprite.h"
/* SDL2 */
#include <SDL2/SDL_image.h>

/* Game_Kaboom */
#include "game.h"
#include "helpers.h"
#include "game_textures.h"


/*******************************************************************************
*
*******************************************************************************/
SDL_Texture* g_textures_arr[GAME_TEXTURES_IDS_SIZE] = { NULL };

_sprite_load_texture(int texture_id)
{
    /* Already loaded - Just returns... */
    if(g_textures_arr[texture_id])
        return g_textures_arr[texture_id];

    /* Texture isn't loaded yet - Load it and save to the textures array */
    SDL_Surface *tmp_surface = IMG_Load(game_textures_ids[texture_id]);
    GAME_VERIFY(tmp_surface,
                "Cannot create surface with filename: %s",
                game_textures_ids[texture_id]);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(g_pRenderer, tmp_surface);
    GAME_VERIFY(texture,
                "Failed to create texture from surface with filename: %s",
                game_textures_ids[texture_id]);

    /* Prevent leak */
    SDL_FreeSurface(tmp_surface);

    g_textures_arr[texture_id] = texture;

    return texture;
}


/*******************************************************************************
*                                                                              *
*******************************************************************************/
void sprite_init(sprite_t *sprite,
                 int texture_id,
                 int frame_w, int frame_h,
                 int frame_x, int frame_y)
{
    sprite->x = frame_x * frame_w;
    sprite->y = frame_y * frame_h;
    sprite->w = frame_w;
    sprite->h = frame_h;

    sprite->texture = _sprite_load_texture(texture_id);

    return sprite;
}

sprite_t sprite_unload(int texture_id)
{
    //COWTODO: Implement.
}

void sprite_draw(sprite_t *sprite, int x, int y)
{
    SDL_Rect src_rect = { sprite->x, sprite->y,
                          sprite->w, sprite->h };
    SDL_Rect dst_rect = { x, y,
                          sprite->w, sprite->h};

    SDL_RenderCopyEx(g_pRenderer,          /* Renderer               */
                     sprite->texture,      /* Texture                */
                     &src_rect, &dst_rect, /* Source and Destination */
                     0,                    /* Angle                  */
                     0,                    /* Center                 */
                     SDL_FLIP_NONE);       /* Flip                   */
}
