/* Header */
#include "sprite.h"
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
    SDL_Surface *tmp_surface = SDL_LoadBMP(game_textures_ids[texture_id]);
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
sprite_t sprite_load(int texture_id)
{
    sprite_t sprite;

    sprite.x       = 0;
    sprite.y       = 0;
    sprite.texture = _sprite_load_texture(texture_id);
    SDL_QueryTexture(sprite.texture, NULL, NULL, &sprite.w, &sprite.h);

    return sprite;
}

sprite_t sprite_unload(int texture_id)
{
    //COWTODO: Implement.
}

void sprite_draw(sprite_t *sprite)
{
    SDL_Rect src_rect = { 0, 0,
                          sprite->w, sprite->h };
    SDL_Rect dst_rect = { sprite->x, sprite->y,
                          sprite->w, sprite->h };

    SDL_RenderCopyEx(g_pRenderer,          /* Renderer               */
                     sprite->texture,      /* Texture                */
                     &src_rect, &dst_rect, /* Source and Destination */
                     0,                    /* Angle                  */
                     0,                    /* Center                 */
                     SDL_FLIP_NONE);       /* Flip                   */
}
