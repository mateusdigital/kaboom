/* Header */
#include "bomb.h"
/* Game_Kaboom */
#include "game_textures.h"

/*******************************************************************************
* Functions                                                                    *
*******************************************************************************/
bomb_t bomb_init(int x, int y, int speed, int max_y)
{
    bomb_t bomb;

    bomb.sprite = sprite_load(game_texture_id_ballon);
    bomb.sprite.x = x;
    bomb.sprite.y = y;

    bomb.state = BOMB_STATE_ALIVE;

    bomb.speed = speed;

    bomb.max_y = max_y;

    return bomb;
}

bomb_update(bomb_t *bomb, float dt)
{
    /* Only move alive bombs */
    if(bomb->state == BOMB_STATE_ALIVE)
    {
        bomb->sprite.y += (bomb->speed * dt);
        if(bomb->sprite.y >= bomb->max_y)
            bomb->state = BOMB_STATE_EXPLODED;
    }
}

bomb_draw(bomb_t *bomb)
{
    /* Do not draw dead bombs */
    if(bomb->state == BOMB_STATE_DEAD)
        return;

    sprite_draw(&(bomb->sprite));
}
