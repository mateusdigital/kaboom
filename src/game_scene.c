/* Header */
#include "game_scene.h"
/* Game */
#include "game.h"
#include "helpers.h"
#include "sprite.h"
#include "game_textures.h"
#include "bomb.h"
#include "bomber.h"
#include "paddle.h"

#define kMaxBombs 200

/*******************************************************************************
* Vars                                                                         *
*******************************************************************************/
bomb_t bombs_arr[kMaxBombs];
int bombs_count = 0;
bomber_t bomber;
paddle_t paddle;

/*******************************************************************************
* Private Functions Declarations                                               *
*******************************************************************************/
void game_on_bomber_drop_bomb(bomber_t *bomber);
void check_bomb_paddle_collision(bomb_t *bomb, paddle_t *paddle);


/*******************************************************************************
* Public Functions Definitions                                                 *
*******************************************************************************/
void game_scene_load()
{
    GAME_LOG("game_scene_load");
    srand(2);

    /* Initialize the Bomber */
    bomber = bomber_init(100, 100, /* x, y         */
                           0, 500, /* min_x, max_x */
                              100, /* speed        */
                               5); /* bombs        */

    bomber.drop_bomb_func = game_on_bomber_drop_bomb;

    /* Initializer the Player */
    paddle = paddle_init(100, 400, 0, 500, 100);
}

void game_scene_unload()
{
    GAME_LOG("game_scene_unload");
}

void game_scene_update(float dt)
{
    GAME_LOG("game_scene_update");

    /* Get the input */
    Uint8 *keys = SDL_GetKeyboardState(NULL);
    paddle.direction = 0;
    if(keys[SDL_SCANCODE_LEFT])
        paddle.direction -= 1;
    if(keys[SDL_SCANCODE_RIGHT])
        paddle.direction += 1;


    /* Bombs */
    for(int i = 0; i < bombs_count; ++i)
        bomb_update(&bombs_arr[i], dt);

    /* Bomber */
    bomber_update(&bomber, dt);

    /* Paddles */
    paddle_update(&paddle, dt);

    /* Check collisions */
    for(int i = 0; i < bombs_count; ++i)
        check_bomb_paddle_collision(&bombs_arr[i], &paddle);
}

void game_scene_draw()
{
    GAME_LOG("game_scene_draw");

    /* Bombs */
    for(int i = 0; i < bombs_count; ++i)
        bomb_draw(&bombs_arr[i]);

    /* Bomber */
    bomber_draw(&bomber);

    /* Paddles */
    paddle_draw(&paddle);
}

void game_scene_handle_event(SDL_Event *event)
{
    GAME_LOG("game_scene_handle");
}


/*******************************************************************************
* Private Functions Definitions                                                *
*******************************************************************************/
void game_on_bomber_drop_bomb(bomber_t *bomber)
{
    bombs_arr[bombs_count] = bomb_init(bomber->sprite.x,
                                       bomber->sprite.y,
                                       50,
                                       SCREEN_HEIGHT);
    ++bombs_count;
}
void check_bomb_paddle_collision(bomb_t *bomb, paddle_t *paddle)
{
    SDL_Rect bomb_rect = { bomb->sprite.x, bomb->sprite.y,
                           bomb->sprite.w, bomb->sprite.h };

    int first_index = paddle->paddle_first_available_index;
    int last_index  = paddle->paddle_last_available_index;

    SDL_Rect paddle_rect = { paddle->sprites[first_index].x,
    /* +------+ Y1 */        paddle->sprites[first_index].y,
    /* +------+    */        paddle->sprites[first_index].w,
    /*             */     /* Here we are setting the height of the rectangle */
    /* +------+ Y2 */     /* as the sum of top of higher paddle(Y1) + the    */
    /* +------+ H2 */     /* top of the lower paddle(Y2 + the height of      */
                          /* lower (H2), this makes the rect fill the        */
                          /* entire range that paddles can touch.            */
                             paddle->sprites[first_index].y +  /* Y1 */
                             paddle->sprites[last_index].y  +  /* Y2 */
                             paddle->sprites[first_index].h }; /* H2 */

    if(SDL_HasIntersection(&bomb_rect, &paddle_rect))
    {
        bomb->state = BOMB_STATE_DEAD;
    }
}
