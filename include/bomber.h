#ifndef __Game_Kaboom_include_bomber_h__
#define __Game_Kaboom_include_bomber_h__

/* Game_Kaboom */
#include "sprite.h"


/*******************************************************************************
* Constants                                                                    *
*******************************************************************************/
enum {
    BOMBER_SPRITES_COUNT =  3,
};


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


typedef struct _bomber_options_t
{
    int bombs_remaining;
    int bombs_dropped;

    float seconds_between_drops;
    float seconds_since_last_drop;

} bomber_options_t;


typedef struct _bomber_t
{
    /* Sprites */
    sprite_t sprites[BOMBER_SPRITES_COUNT];
    int current_frame_index;

    /* Bombs */
    bomber_options_t bomber_options;

    /* Boundaries */
    int min_x, max_x;

    /* Movement */
    int x, y;
    int speed;
    int target_x;

    /* State */
    bomber_state_t state;

    /* Callback */
    void (*drop_bomb_func)(struct _bomber_t *bomber);

} bomber_t;


/*******************************************************************************
* Functions                                                                    *
*******************************************************************************/
/* Init / Clean */
void bomber_init(bomber_t *bomber, void (*callback)(bomber_t *bomber));

void bomber_clean(bomber_t *bomber);

/* Reset */
void bomber_reset(bomber_t *bomber, bomber_options_t options);

/* Win / Lose */
void bomber_win(bomber_t *bomber);
void bomber_lose(bomber_t *bomber);

/* Update / Draw */
void bomber_update(bomber_t *bomber, float dt);
void bomber_draw  (bomber_t *bomber);

#endif /* __Game_Kaboom_include_bomber_h__ */
