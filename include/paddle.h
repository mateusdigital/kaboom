#ifndef __Game_Kaboom_include_paddle_h__
#define __Game_Kaboom_include_paddle_h__

/* Game_Kaboom */
#include "sprite.h"
#include "bomb.h"

/*******************************************************************************
* Constants                                                                    *
*******************************************************************************/
enum {
    PADDLE_SPRITE_W = 84,
    PADDLE_SPRITE_H = 45,

    PADDLE_OFFSET_Y = 15,

    PADDLE_SPRITES_SIZE = 4,

    PADDLE_DIR_LEFT  = -1,
    PADDLE_DIR_NONE  =  0,
    PADDLE_DIR_RIGHT =  1,

    PADDLE_MAX_LIVES = 3,

    PADDLE_SPEED = 200,
};


/*******************************************************************************
* Types                                                                        *
*******************************************************************************/
typedef struct _paddle_hit_animation_t
{
    int   current_sprite_index;
    float time_to_change_frame;
    float time_since_last_frame_change;

    int enabled;

}paddle_hit_animation_t;


typedef struct _paddle_t
{
    /* Sprite */
    sprite_t               sprites   [PADDLE_SPRITES_SIZE];
    paddle_hit_animation_t animations[PADDLE_SPRITES_SIZE];

    /* Paddle Info */
    int lives;

    /* Boundaries */
    int min_x, max_x;

    /* Movement */
    int x, y;
    int speed;
    int direction;

} paddle_t;


/*******************************************************************************
* Functions                                                                    *
*******************************************************************************/
/* Init */
void paddle_init(paddle_t *paddle);

/* Actions */
void paddle_reset(paddle_t *paddle);
void paddle_kill (paddle_t *paddle);
void paddle_change_direction(paddle_t *paddle, int direction);

/* Helpers */
int paddle_check_collision_with_bomb(paddle_t *paddle, bomb_t *bomb);

/* Update / Draw */
void paddle_update(paddle_t *paddle, float dt);
void paddle_draw  (paddle_t *paddle);

#endif /* __Game_Kaboom_include_paddle_h__ */
