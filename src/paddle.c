/* Header */
#include "paddle.h"
/* Game_Kaboom */
#include "game.h"
#include "helpers.h"
#include "game_textures.h"


/*******************************************************************************
* Private Constants                                                            *
*******************************************************************************/
enum {
    PADDLE_SPRITE_NORMAL_INDEX = 0,
};

#define PADDLE_FRAME_TIME 0.3f


/*******************************************************************************
* Functions                                                                    *
*******************************************************************************/
/* Init */
void paddle_init(paddle_t *paddle)
{
     /* Sprite */
    for(int i = 0; i < PADDLE_SPRITES_SIZE; ++i)
    {
        sprite_init(&paddle->sprites[i],
                    game_texture_id_paddle,
                    PADDLE_SPRITE_W, PADDLE_SPRITE_H,
                    i, 0);


        paddle->animations[i].current_sprite_index         = 0;
        paddle->animations[i].time_to_change_frame         = PADDLE_FRAME_TIME;
        paddle->animations[i].time_since_last_frame_change = 0;
        paddle->animations[i].enabled                      = 1;
    }

    /* Paddle Info */
    paddle->lives = PADDLE_MAX_LIVES;

    /* Boundaries */
    paddle->min_x = 0;
    paddle->max_x = SCREEN_WIDTH - PADDLE_SPRITE_W;

    /* Movement */
    paddle->x = (SCREEN_WIDTH / 2) - (PADDLE_SPRITE_W / 2);
    paddle->y = SCREEN_HEIGHT - (PADDLE_OFFSET_Y * PADDLE_MAX_LIVES)
                - (PADDLE_SPRITE_H * PADDLE_MAX_LIVES);
    paddle->speed     = PADDLE_SPEED;
    paddle->direction = PADDLE_DIR_NONE;
}

/* Actions */
void paddle_reset(paddle_t *paddle)
{

}

void paddle_kill(paddle_t *paddle)
{
    --paddle->lives;
}

void paddle_change_direction(paddle_t *paddle, int direction)
{
    paddle->direction = direction;
}

/* Helpers */
void paddle_check_collision_with_bomb(paddle_t *paddle, bomb_t *bomb)
{
    for(int i = 0; i < paddle->lives; ++i)
    {
        SDL_Rect r1 = { paddle->x,
                        paddle->y + (PADDLE_SPRITE_H * i) + (PADDLE_OFFSET_Y * i),
                        PADDLE_SPRITE_W,
                        PADDLE_SPRITE_H };

        SDL_Rect r2 = bomb_get_hitbox(bomb);

        if(SDL_HasIntersection(&r1, &r2))
        {
            bomb_kill(bomb);
            paddle->animations[i].enabled = 1;
        }
    }
}


/* Update / Draw */
void paddle_update(paddle_t *paddle, float dt)
{
    /* Move */
    paddle->x += paddle->direction * paddle->speed * dt;

    /* Make the paddle stay in bounds */
    if(paddle->x <= paddle->min_x)
        paddle->x = paddle->min_x;
    else if(paddle->x >= paddle->max_x)
        paddle->x = paddle->max_x;

    /* Animation */
    for(int i = 0; i < paddle->lives; ++i)
    {
        paddle_hit_animation_t *anim = &(paddle->animations[i]);

        GAME_LOG("i %d - %d", i, anim->enabled);
        if(!anim->enabled)
            continue;

        anim->time_since_last_frame_change += dt;
        if(anim->time_since_last_frame_change > anim->time_to_change_frame)
        {
            anim->time_since_last_frame_change -= anim->time_to_change_frame;
            anim->current_sprite_index = (anim->current_sprite_index + 1)
                                          % PADDLE_SPRITES_SIZE;

            if(anim->current_sprite_index == 0)
                anim->enabled = 0;
        }
    }
}

void paddle_draw(paddle_t *paddle)
{
    /* The other paddles aren't animated and could not exists */
    for(int i = 0; i < paddle->lives; ++i)
    {
        int index = paddle->animations[i].current_sprite_index;
        sprite_draw(&paddle->sprites[index],
                    paddle->x,
                    paddle->y + (PADDLE_SPRITE_H * i) + (PADDLE_OFFSET_Y * i));
    }
}
