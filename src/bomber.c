/* Header */
#include "bomber.h"
/* std */
#include <stdlib.h>
#include <time.h>
/* Game_Kaboom */
#include "game.h"
#include "game_textures.h"


/*******************************************************************************
* Private Constants                                                            *
*******************************************************************************/
enum {
    BOMBER_SPRITE_FRAME_W       = 43,
    BOMBER_SPRITE_FRAME_H       = 90,

    BOMBER_SPRITE_INDEX_DEAD    =  0,
    BOMBER_SPRITE_INDEX_WAITING =  1,
    BOMBER_SPRITE_INDEX_MOVING  =  2,

    BOMBER_SPEED = 100,
};


/*******************************************************************************
* Private Functions Declarations                                               *
*******************************************************************************/
void _init_sprite(bomber_t *bomber, int sprite_index);


/*******************************************************************************
* Public Functions Definitions                                                 *
*******************************************************************************/
void bomber_init(bomber_t *bomber, void (*callback)(bomber_t *bomber))
{
    /* Sprites */
    _init_sprite(bomber, BOMBER_SPRITE_INDEX_DEAD   );
    _init_sprite(bomber, BOMBER_SPRITE_INDEX_WAITING);
    _init_sprite(bomber, BOMBER_SPRITE_INDEX_MOVING );

    /* Boundaries */
    bomber->min_x = 0;
    bomber->max_x = SCREEN_WIDTH - BOMBER_SPRITE_FRAME_W;

    /* Callback */
    bomber->drop_bomb_func = callback;

    /* Start losing */
    bomber_lose(bomber);

    return bomber;
}

/* Reset */
void bomber_reset(bomber_t *bomber, bomber_options_t options)
{
    bomber->state               = BOMBER_STATE_WAITING;
    bomber->current_frame_index = BOMBER_SPRITE_INDEX_WAITING;
    bomber->bomber_options      = options;
}

/* Win / Lose */
void bomber_win(bomber_t *bomber)
{
    bomber->state               = BOMBER_STATE_WAITING;
    bomber->current_frame_index = BOMBER_SPRITE_INDEX_WAITING;

    bomber->bomber_options.bombs_remaining = 0;
}
void bomber_lose(bomber_t *bomber)
{
    bomber->state               = BOMBER_STATE_DEAD;
    bomber->current_frame_index = BOMBER_SPRITE_INDEX_DEAD;

    bomber->bomber_options.bombs_remaining = 0;
}



void bomber_update(bomber_t *bomber, float dt)
{
    /* Waiting
       1 - Check there is bomb to drop.
       2 - If so, selected a new drop stop.
    */
    if(bomber->state == BOMBER_STATE_WAITING)
    {
        bomber->current_frame_index = BOMBER_SPRITE_INDEX_WAITING;

        /* Wait for next turn */
        if(bomber->bomber_options.bombs_dropped >=
           bomber->bomber_options.bombs_remaining)
        {
            return;
        }

        /* Change the state and select a new drop stop */
        bomber->state    = BOMBER_STATE_MOVING;
        bomber->target_x = bomber->min_x + (rand() % bomber->max_x);
        bomber->speed    = (bomber->x >= bomber->target_x)
                           ? -BOMBER_SPEED
                           : +BOMBER_SPEED;
    }

    /* Moving
       1 - Check if we reach the drop stop.
       2 - Keep going to the drop stop.
    */
    else if(bomber->state == BOMBER_STATE_MOVING)
    {
        bomber->current_frame_index = BOMBER_SPRITE_INDEX_MOVING;
        bomber->x += (bomber->speed * dt);

        /* We reach the drop spot -> Drop the bomb MUAMAUAMUA */
        if(bomber->speed < 0 && bomber->x < bomber->target_x)
            bomber->state = BOMBER_STATE_DROPPING;
        else if(bomber->speed > 0 && bomber->x > bomber->target_x)
            bomber->state = BOMBER_STATE_DROPPING;
    }
    /* Dropping
       1 - Check if we wait enough time to drop the bomb.
       2 - Drop the bomb and inform the listeners
    */
    else if(bomber->state == BOMBER_STATE_DROPPING)
    {
        bomber->current_frame_index = BOMBER_SPRITE_INDEX_MOVING;

        bomber->bomber_options.seconds_since_last_drop += dt;

        /* We wait enough -> Drop the bomb, reset timers and inform listeners */
        if(bomber->bomber_options.seconds_since_last_drop >=
           bomber->bomber_options.seconds_between_drops)
        {
            bomber->bomber_options.seconds_since_last_drop -= bomber->bomber_options.seconds_between_drops;
            bomber->state = BOMBER_STATE_WAITING;

            bomber->bomber_options.bombs_dropped++;
            bomber->drop_bomb_func(bomber);
        }
    }
}

void bomber_draw(bomber_t *bomber)
{
    sprite_draw(&bomber->sprites[bomber->current_frame_index],
                bomber->x, bomber->y);
}


/*******************************************************************************
* Private Functions Definitions                                                *
*******************************************************************************/
void _init_sprite(bomber_t *bomber, int sprite_index)
{
    sprite_init(&bomber->sprites[sprite_index],
                 game_texture_id_bomber,
                 BOMBER_SPRITE_FRAME_W, BOMBER_SPRITE_FRAME_H,
                 sprite_index, 0);
}
