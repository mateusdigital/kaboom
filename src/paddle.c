/* Header */
#include "paddle.h"
/* Game_Kaboom */
#include "game_textures.h"

/*******************************************************************************
* CONSTANTS                                                                    *
*******************************************************************************/
#define PADDLE_OFFSET_Y 10


/*******************************************************************************
* Functions                                                                    *
*******************************************************************************/
paddle_t paddle_init(int     x, int     y,
                     int min_x, int max_x,
                     int speed)
{
    paddle_t paddle;

//    for(int i = 0; i < MAX_PADDLES_COUNT; ++i)
//    {
//        paddle.sprites[i]   = sprite_load(game_texture_id_vulture2);
//        paddle.sprites[i].x = x;
//        paddle.sprites[i].y = y + ((paddle.sprites[i].h + PADDLE_OFFSET_Y) * i);
//    }

    paddle.paddles_remaining            = MAX_PADDLES_COUNT;
    paddle.paddle_first_available_index = 0;
    paddle.paddle_last_available_index  = paddle.paddles_remaining -1;

    paddle.min_x = min_x;
    paddle.max_x = max_x;

    paddle.speed     = speed;
    paddle.direction = 0;

    return paddle;
}

void paddle_update(paddle_t *paddle, float dt)
{
    int displacement = (paddle->speed * paddle->direction * dt);

    for(int i  = paddle->paddle_first_available_index;
            i <= paddle->paddle_last_available_index;
        ++i)
    {
        /* Update the position */
        sprite_t *sprite = &paddle->sprites[i];
        sprite->x += displacement;

        /* Mantain the paddle into the boundaries */
        if(sprite->x <= paddle->min_x)
            sprite->x = paddle->min_x;
        else if(sprite->x + sprite->w >= paddle->max_x)
            sprite->x = paddle->max_x - sprite->w;
    }
}

void paddle_draw(paddle_t *paddle)
{
    /* Only draw the still available paddles */
    for(int i  = paddle->paddle_first_available_index;
            i <= paddle->paddle_last_available_index;
        ++i)
    {
//        sprite_draw(&paddle->sprites[i]);
    }
}
