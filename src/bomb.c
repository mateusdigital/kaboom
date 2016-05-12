/* Header */
#include "bomb.h"
/* Game_Kaboom */
#include "game_textures.h"


/*******************************************************************************
* Private Constants                                                            *
*******************************************************************************/
enum {
    BOMB_ALIVE_SPRITE_FRAME_W = 30,
    BOMB_ALIVE_SPRITE_FRAME_H = 45,

    BOMB_EXPLODED_SPRITE_FRAME_W = 48,
    BOMB_EXPLODED_SPRITE_FRAME_H = 45,

    BOMB_SPEED = 100,
};

#define BOMB_FRAME_TIME_ALIVE    0.4f
#define BOMB_FRAME_TIME_EXPLODED 0.2f


/*******************************************************************************
* Functions                                                                    *
*******************************************************************************/
void bomb_init(bomb_t *bomb, void (*callback)(void))
{
    /* Alive Sprites */
    for(int i = 0; i < BOMB_ALIVE_SPRITES_SIZE; ++i)
    {
        sprite_init(&bomb->alive_sprites_arr[i],
                    game_texture_id_bomb_alive,
                    BOMB_ALIVE_SPRITE_FRAME_W, BOMB_ALIVE_SPRITE_FRAME_H,
                    i, 0);
    }

    /* Exploded Sprites */
    for(int i = 0; i < BOMB_EXPLODED_SPRITES_SIZE; ++i)
    {
        sprite_init(&bomb->exploted_sprites_arr[i],
                    game_texture_id_bomb_exploded,
                    BOMB_EXPLODED_SPRITE_FRAME_W, BOMB_EXPLODED_SPRITE_FRAME_H,
                    i, 0);
    }

    bomb->current_sprite_index      = 0;
    bomb->max_sprite_index          = 0;
    bomb->time_since_last_animation = 0;
    bomb->time_to_change_frame      = 0;

    /* State */
    bomb->state = BOMB_STATE_DEAD;

    /* Movement */
    bomb->x     = 0;
    bomb->y     = 0;
    bomb->speed = 0;
    bomb->max_y = 0;

    /* Callback */
    bomb->reach_target_func = callback;
}

/* Actions */
void bomb_reset(bomb_t *bomb, int x, int y, int speed, int max_y)
{
    /* Sprites */
    bomb->current_sprite_index      = 0;
    bomb->max_sprite_index          = BOMB_ALIVE_SPRITES_SIZE;
    bomb->time_since_last_animation = 0;
    bomb->time_to_change_frame      = BOMB_FRAME_TIME_ALIVE;

    /* State */
    bomb->state = BOMB_STATE_ALIVE;

    /* Movement */
    bomb->x     = x;
    bomb->y     = y;
    bomb->speed = speed;
    bomb->max_y = max_y;
}

void bomb_kill(bomb_t *bomb)
{
    bomb->state = BOMB_STATE_DEAD;
}

void bomb_explode(bomb_t *bomb)
{
    /* Dead bombs doesn't explode :D */
    if(bomb->state == BOMB_STATE_DEAD)
        return;

    /* Sprites */
    bomb->current_sprite_index      = 0;
    bomb->max_sprite_index          = BOMB_EXPLODED_SPRITES_SIZE;
    bomb->time_since_last_animation = 0;
    bomb->time_to_change_frame      = BOMB_FRAME_TIME_EXPLODED;

    /* State */
    bomb->state = BOMB_STATE_EXPLODED;
}

/* Helpers */
SDL_Rect bomb_get_hitbox(bomb_t *bomb)
{
    return (SDL_Rect) {
        .x = bomb->x,
        .y = bomb->y,
        .w = BOMB_ALIVE_SPRITE_FRAME_W,
        .h = BOMB_ALIVE_SPRITE_FRAME_H
    };
}

/* Update / Draw */
void bomb_update(bomb_t *bomb, float dt)
{
    /* Only move alive bombs */
    if(bomb->state == BOMB_STATE_ALIVE)
    {
        bomb->y += (bomb->speed * dt);
        if(bomb->y >= bomb->max_y)
            bomb->reach_target_func();
    }

    bomb->time_since_last_animation += dt;
    if(bomb->time_since_last_animation >= bomb->time_to_change_frame)
    {
        bomb->time_since_last_animation -= bomb->time_to_change_frame;
        bomb->current_sprite_index = (bomb->current_sprite_index + 1)
                                      % bomb->max_sprite_index;
    }
}

void bomb_draw(bomb_t *bomb)
{
    /* Do not draw dead bombs */
    //if(bomb->state == BOMB_STATE_DEAD)
    //    return;

    int index = 0;bomb->current_sprite_index;
    sprite_t *sprite = (bomb->state == BOMB_STATE_ALIVE)
                        ? &bomb->alive_sprites_arr   [index]
                        : &bomb->exploted_sprites_arr[index];

    sprite_draw(sprite, bomb->x, bomb->y);
}
