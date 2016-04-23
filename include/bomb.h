#ifndef __Game_Kaboom_include_bomb_h__
#define __Game_Kaboom_include_bomb_h__

/* Game_Kaboom */
#include "sprite.h"


/*******************************************************************************
* Types                                                                        *
*******************************************************************************/
typedef enum _bomb_state_t
{
    BOMB_STATE_ALIVE,
    BOMB_STATE_DEAD,
    BOMB_STATE_EXPLODED

}bomb_state_t;


typedef struct _bomb_t
{
    sprite_t     sprite;
    bomb_state_t state;
    int          speed;
    int          max_y;

} bomb_t;


/*******************************************************************************
* Functions                                                                    *
*******************************************************************************/
bomb_t bomb_init(int x, int y, int speed, int max_y);

bomb_update(bomb_t *bomb, float dt);
bomb_draw  (bomb_t *bomb);

#endif // __Game_Kaboom_include_bomb_h__
