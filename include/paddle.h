#ifndef PADDLE_H_INCLUDED
#define PADDLE_H_INCLUDED

/* Game_Kaboom */
#include "sprite.h"


/*******************************************************************************
* Constants                                                                    *
*******************************************************************************/
#define MAX_PADDLES_COUNT 3


/*******************************************************************************
* Types                                                                        *
*******************************************************************************/
typedef struct _paddle_t
{
    /* Sprite */
    sprite_t sprites[MAX_PADDLES_COUNT];

    /* Paddle Info */
    int paddles_remaining;
    int paddle_first_available_index;
    int paddle_last_available_index;

    /* Boundaries */
    int min_x, max_x;

    /* Movement */
    int speed;
    int direction;

} paddle_t;


/*******************************************************************************
* Functions                                                                    *
*******************************************************************************/
paddle_t paddle_init(int     x, int     y,
                     int min_x, int max_x,
                     int speed);

void paddle_update(paddle_t *paddle, float dt);
void paddle_draw(paddle_t *paddle);


#endif // PADDLE_H_INCLUDED //
