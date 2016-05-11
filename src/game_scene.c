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


/*******************************************************************************
* Private Constants                                                            *
*******************************************************************************/
enum {
    GAME_SCENE_BOMBS_ARR_SIZE = 100,
};


/*******************************************************************************
* Vars                                                                         *
*******************************************************************************/
int      current_turn;
bomber_t bomber;
bomb_t*  bombs_arr[GAME_SCENE_BOMBS_ARR_SIZE];


/*******************************************************************************
* Private Functions Declarations                                               *
*******************************************************************************/
/* Turn Management */
void _new_turn(void);
void _reset_turn(void);

/* Reset and Helpers */
void _reset_bomber(void);
void _reset_bomb(bomb_t *bomb);
void _reset_all_availale_bombs();
bomb_t* _get_first_available_bomb();

/* Game Objects Callbacks */
void _on_bomber_drop_bomb(bomber_t *bomber);
void _on_bomb_reach_target();

/* Others */
void _check_bomb_paddle_collision(bomb_t *bomb, paddle_t *paddle);


/*******************************************************************************
* Public Functions Definitions                                                 *
*******************************************************************************/
void game_scene_load()
{
    GAME_LOG("game_scene_load");
    srand(2);

    /* */
    current_turn = 0;

    /* Initialize the Bomber */
    bomber_init(&bomber,
                0,
                SCREEN_WIDTH,
                _on_bomber_drop_bomb);
}

void game_scene_unload()
{
    GAME_LOG("game_scene_unload");
}

void game_scene_update(float dt)
{
    /* Bomber */
    bomber_update(&bomber, dt);

    /* Bombs */
    for(int i = 0; i < GAME_SCENE_BOMBS_ARR_SIZE; ++i)
    {
        bomb_t *b = bombs_arr[i];
        if(!b) break;

        bomb_update(b, dt);
    }

    Uint8 *keys = SDL_GetKeyboardState(NULL);
    if(keys[SDL_SCANCODE_SPACE])
        _reset_turn();
}

void game_scene_draw()
{
    /* Bomber */
    bomber_draw(&bomber);

    /* Bombs */
    for(int i = 0; i < GAME_SCENE_BOMBS_ARR_SIZE; ++i)
    {
        bomb_t *b = bombs_arr[i];
        if(!b) break;

        bomb_draw(b);
    }
}

void game_scene_handle_event(SDL_Event *event)
{}


/*******************************************************************************
* Private Functions Definitions                                                *
*******************************************************************************/
/* Turn Management */
void _new_turn(void)
{
    ++current_turn;
    _reset_turn();
}
void _reset_turn(void)
{
    if(current_turn == 0)
        _new_turn();

    _reset_bomber();
    _reset_all_availale_bombs();
}


/* Reset and Helpers */
void _reset_bomber(void)
{
    bomber_options_t opt;

    opt.bombs_dropped           = 0;
    opt.bombs_remaining         = 10;
    opt.seconds_between_drops   = 1;
    opt.seconds_since_last_drop = 0;

    bomber_reset(&bomber, opt);
}

void _reset_bomb(bomb_t *bomb)
{
    bomb_reset(bomb,
               bomber.x, bomber.y,
               50,
               SCREEN_HEIGHT);
}
void _reset_all_availale_bombs()
{
    for(int i = 0; i < GAME_SCENE_BOMBS_ARR_SIZE; ++i)
    {
        if(bombs_arr[i] == NULL)
            break;
        _reset_bomb(bombs_arr[i]);
    }
}
bomb_t* _get_first_available_bomb()
{
    for(int i = 0; i < GAME_SCENE_BOMBS_ARR_SIZE; ++i)
    {
        if(bombs_arr[i] == NULL)
        {
            bombs_arr[i] = malloc(sizeof(bomb_t));
            bomb_init(bombs_arr[i], _on_bomb_reach_target);

            return bombs_arr[i];
        }

        else if(bombs_arr[i]->state == BOMB_STATE_DEAD)
        {
            return bombs_arr[i];
        }
    }
}

/* Game Object Callbacks */
void _on_bomber_drop_bomb(bomber_t *bomber)
{
    bomb_t *bomb = _get_first_available_bomb();
    _reset_bomb(bomb);
}
void _on_bomb_reach_target()
{
    /* Make all bombs to explode */
    for(int i = 0; i < GAME_SCENE_BOMBS_ARR_SIZE; ++i)
    {
        bomb_t *bomb = bombs_arr[i];
        if(!bomb) break;

        bomb_explode(bomb);
    }

    /* Make bomber win */
    bomber_win(&bomber);
}

void _check_bomb_paddle_collision(bomb_t *bomb, paddle_t *paddle)
{
}
