#ifndef BOMBER_H_INCLUDED
#define BOMBER_H_INCLUDED

/* Game_Kaboom */
#include "sprite.h"


/*******************************************************************************
* Types                                                                        *
*******************************************************************************/
typedef enum _bomber_state_t
{
    BOMBER_STATE_WAITING,
    BOMBER_STATE_DROPPING,
    BOMBER_STATE_MOVING,
    BOMBER_STATE_DEAD

} bomber_state_t;

typedef struct _bomber_t
{
    /* Sprites */
    sprite_t sprite;

    /* Bombs */
    int   bombs_to_drop;
    int   bombs_dropped;
    float seconds_between_drops;
    float seconds_since_last_drop;

    /* Boundaries */
    int min_x, max_x;
    int target_x;

    /* Speed */
    int speed;

    /* State */
    bomber_state_t state;

    /* Callback */
    void (*drop_bomb_func)(struct _bomber_t *bomber);

} bomber_t;


/*******************************************************************************
* Functions                                                                    *
*******************************************************************************/
bomber_t bomber_init(int     x, int     y,
                     int min_x, int max_x,
                     int speed,
                     int bombs_to_drop);

void bomber_update(bomber_t *bomber, float dt);
void bomber_draw(bomber_t *bomber);

#endif // BOMBER_H_INCLUDED
