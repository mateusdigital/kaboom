#ifndef __Game_Kaboom_include_bomb_h__
#define __Game_Kaboom_include_bomb_h__

/* Game_Kaboom */
#include "sprite.h"


/*******************************************************************************
* Constants                                                                    *
*******************************************************************************/
enum {
    BOMB_ALIVE_SPRITES_SIZE    = 4,
    BOMB_EXPLODED_SPRITES_SIZE = 3,
};

/*******************************************************************************
* Types                                                                        *
*******************************************************************************/
typedef enum _bomb_state_t
{
    BOMB_STATE_ALIVE,
    BOMB_STATE_DEAD,
    BOMB_STATE_EXPLODED,

}bomb_state_t;


typedef struct _bomb_t
{
    /* Sprites */
    sprite_t alive_sprites_arr   [BOMB_ALIVE_SPRITES_SIZE];
    sprite_t exploted_sprites_arr[BOMB_EXPLODED_SPRITES_SIZE];
    int      current_sprite_index;
    int      max_sprite_index;
    float    time_since_last_animation;
    float    time_to_change_frame;

    /* State */
    bomb_state_t state;

    /* Movement */
    int x, y;
    int speed;
    int max_y;

    /* Callback */
    void (*reach_target_func)(void);

} bomb_t;


/*******************************************************************************
* Functions                                                                    *
*******************************************************************************/
/* Init / Clean */
void bomb_init(bomb_t *bomb, void (*callback)(void));

/* Actions */
void bomb_reset(bomb_t *bomb,
                int x, int y,
                int speed, int max_y);

void bomb_explode(bomb_t *bomb);

/* Update / Draw */
void bomb_update(bomb_t *bomb, float dt);
void bomb_draw  (bomb_t *bomb);

#endif /* __Game_Kaboom_include_bomb_h__ */
