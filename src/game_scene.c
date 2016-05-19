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
* Private Types                                                                *
*******************************************************************************/
typedef enum _game_state_t
{
    GAME_STATE_VICTORY,
    GAME_STATE_DEFEAT,
    GAME_STATE_GAME_OVER,

    GAME_STATE_PLAY,
    GAME_STATE_PAUSED,

}game_state_t;


/*******************************************************************************
* Vars                                                                         *
*******************************************************************************/
int          current_turn;
int          bombs_caught_count;
game_state_t game_state;

bomber_t bomber;
bomb_t*  bombs_arr[GAME_SCENE_BOMBS_ARR_SIZE];
paddle_t paddle;


/*******************************************************************************
* Private Functions Declarations                                               *
*******************************************************************************/
/* */
void _handle_input       (void);
void _update_game_objects(float dt);
void _check_collisions   (void);
void _check_game_state   (void);


/* State Management */
void _change_state_victory  (void);
void _change_state_defeat   (void);
void _change_state_game_over(void);
void _change_state_play     (void);
void _change_state_pause    (void);

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


/*******************************************************************************
* Public Functions Definitions                                                 *
*******************************************************************************/
void game_scene_load()
{
    GAME_LOG("game_scene_load");
    srand(2);

    /* Init Objects */
    bomber_init(&bomber, _on_bomber_drop_bomb);
    paddle_init(&paddle);

    _change_state_game_over();
}

void game_scene_unload()
{
    GAME_LOG("game_scene_unload");
}

void game_scene_update(float dt)
{
    _handle_input       ();
    _update_game_objects(dt);
    _check_collisions   ();
    _check_game_state   ();
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

    /* Paddle */
    paddle_draw(&paddle);
}

void game_scene_handle_event(SDL_Event *event)
{}


/*******************************************************************************
* Private Functions Definitions                                                *
*******************************************************************************/
/* */
void _handle_input(void)
{
    Uint8 *keys = SDL_GetKeyboardState(NULL);

#define IF_KD(_key_) if(keys[SDL_SCANCODE_##_key_])

    /* GameOver State - Just handle the space key */
    if(game_state == GAME_STATE_GAME_OVER ||
       game_state == GAME_STATE_VICTORY)
    {
        IF_KD(SPACE) _new_turn();
    }

    /* Victory / Defeat States - Just Handle the space key */
    else if(game_state == GAME_STATE_DEFEAT)
    {
        IF_KD(SPACE) _reset_turn();
    }

    /* Play State - Handle the paddle movement and the pause action */
    else if(game_state == GAME_STATE_PLAY)
    {
        paddle_change_direction(&paddle, PADDLE_DIR_NONE);
        /* Paddle Movement */
        IF_KD(LEFT ) paddle_change_direction(&paddle, PADDLE_DIR_LEFT);
        IF_KD(RIGHT) paddle_change_direction(&paddle, PADDLE_DIR_RIGHT);

        /* Pause Action */
        IF_KD(SPACE) _change_state_pause();
    }

    /* Pause State - Just handle the resumeaction */
    else if(game_state == GAME_STATE_PAUSED)
    {
        IF_KD(SPACE) _change_state_play();
    }

#undef IF_KD
}

void _update_game_objects(float dt)
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

    /* Paddle */
    paddle_update(&paddle, dt);
}

void _check_collisions(void)
{
    /* Check Collisions */
    for(int i = 0; i < GAME_SCENE_BOMBS_ARR_SIZE; ++i)
    {
        bomb_t *bomb = bombs_arr[i];
        if(!bomb)
            break;

        if(bomb->state != BOMB_STATE_ALIVE)
            continue;

        if(paddle_check_collision_with_bomb(&paddle, bomb))
        {
            ++bombs_caught_count;

            GAME_LOG("Bombs Caught %d - Total Bombs %d",
                     bombs_caught_count,
                     bomber.bomber_options.bombs_total);
        }
    }
}

void _check_game_state(void)
{
    /* Check for turn Victory */
    if(game_state == GAME_STATE_PLAY)
    {
        if(bombs_caught_count == bomber.bomber_options.bombs_total)
            _change_state_victory();
    }

    /* */
}


/* State Management */
void _change_state_victory(void)
{
    GAME_LOG("Change state Victory");
    game_state = GAME_STATE_VICTORY;
    bomber_lose(&bomber);
}
void _change_state_defeat(void)
{
    GAME_LOG("Change state Defeat");
    game_state = GAME_STATE_DEFEAT;
    bomber_win(&bomber);
}
void _change_state_game_over(void)
{
    GAME_LOG("Change state Game Over");
    game_state = GAME_STATE_GAME_OVER;
    bomber_win(&bomber);
}
void _change_state_play(void)
{
    GAME_LOG("Change state Play");
    game_state = GAME_STATE_PLAY;
}
void _change_state_pause(void)
{
    GAME_LOG("Change state Pause");
    //game_state = GAME_STATE_PAUSED;
}


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

    _change_state_play();

    _reset_bomber();
    _reset_all_availale_bombs();

    bombs_caught_count = 0;
}


/* Reset and Helpers */
void _reset_bomber(void)
{
    bomber_options_t opt;

    opt.bombs_total   = current_turn;
    opt.bombs_left    = current_turn;
    opt.bombs_dropped = 0;

    opt.seconds_between_drops   = 1;
    opt.seconds_since_last_drop = 0;

    bomber_reset(&bomber, opt);
}

void _reset_bomb(bomb_t *bomb)
{
    bomb_reset(bomb,
               bomber.x, bomber.y,
               50 + (5 * current_turn),
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
}
