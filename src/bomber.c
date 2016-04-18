/* Header */
#include "bomber.h"
/* std */
#include <stdlib.h>
#include <time.h>
/* Game_Kaboom */
#include "game_textures.h"

bomber_t bomber_init(int     x, int     y,
                     int min_x, int max_x,
                     int speed,
                     int bombs_to_drop)
{
    bomber_t bomber;

    bomber.sprite = sprite_load(game_texture_id_slime);
    bomber.sprite.x = x;
    bomber.sprite.y = y;

    bomber.bombs_to_drop           = bombs_to_drop;
    bomber.bombs_dropped           = 0;
    bomber.seconds_between_drops   = 1;
    bomber.seconds_since_last_drop = 0;

    bomber.min_x    = min_x;
    bomber.max_x    = max_x;
    bomber.target_x = 0;

    bomber.speed = speed;

    bomber.state = BOMBER_STATE_WAITING;

    return bomber;
}

void bomber_update(bomber_t *bomber, float dt)
{
    /* Waiting
       1 - Check there is bomb to drop.
       2 - If so, selected a new drop stop.
    */
    if(bomber->state == BOMBER_STATE_WAITING)
    {
        /* Wait for next turn */
        if(bomber->bombs_dropped >= bomber->bombs_to_drop)
            return;

        /* Change the state and select a new drop stop */
        bomber->state    = BOMBER_STATE_MOVING;
        bomber->target_x = bomber->min_x + (rand() % bomber->max_x);
        bomber->speed    = (bomber->sprite.x >= bomber->target_x)
                           ? -100
                           : +100;
    }
    /* Moving
       1 - Check if we reach the drop stop.
       2 - Keep going to the drop stop.
    */
    else if(bomber->state == BOMBER_STATE_MOVING)
    {
        bomber->sprite.x += (bomber->speed * dt);

        /* We reach the drop spot -> Drop the bomb MUAMAUAMUA */
        if(bomber->speed < 0 && bomber->sprite.x < bomber->target_x)
            bomber->state = BOMBER_STATE_DROPPING;
        else if(bomber->speed > 0 && bomber->sprite.x > bomber->target_x)
            bomber->state = BOMBER_STATE_DROPPING;
    }
    /* Dropping
       1 - Check if we wait enough time to drop the bomb.
       2 - Drop the bomb and inform the listeners
    */
    else if(bomber->state == BOMBER_STATE_DROPPING)
    {
        bomber->seconds_since_last_drop += dt;

        /* We wait enough -> Drop the bomb, reset timers and inform listeners */
        if(bomber->seconds_since_last_drop >=
           bomber->seconds_between_drops)
        {
            bomber->seconds_since_last_drop -= bomber->seconds_between_drops;
            bomber->state = BOMBER_STATE_WAITING;

            bomber->bombs_dropped++;
            bomber->drop_bomb_func(bomber);
        }
    }
}

void bomber_draw(bomber_t *bomber)
{
    sprite_draw(&bomber->sprite);
}
