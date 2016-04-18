/* Header */
#include "game.h"
/* Game_Kaboom */
#include "helpers.h"
#include "game_scene.h"

/*******************************************************************************
* Constants                                                                    *
*******************************************************************************/
const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 600;


/*******************************************************************************
* Globals                                                                      *
*******************************************************************************/
/* Public */
SDL_Window   *g_pWindow   = NULL;
SDL_Renderer *g_pRenderer = NULL;
int           g_isRunning = 0;
/* Private */
scene_t scenes_arr[100];
scenes_arr_count  = 0;
scenes_curr_index = 0;


/*******************************************************************************
* Private Function Prototypes                                                  *
*******************************************************************************/
void game_update       (float dt);
void game_render       (void    );
void game_handle_events(void    );


/*******************************************************************************
* Game Lifecycle                                                               *
*******************************************************************************/
/* Game Loop */
void game_init(const char *window_name,
               int         sdl_window_flags,
               int         sdl_renderer_flags)
{
    GAME_LOG("Initializing SDL.");

    /* SDL Initialization */
    GAME_VERIFY(SDL_Init(SDL_INIT_EVERYTHING) >= 0,
                "SDL could not initialize.");

    /* Window Initialization */
    g_pWindow = SDL_CreateWindow(window_name,            /* Caption */
                                 SDL_WINDOWPOS_CENTERED, /* X       */
                                 SDL_WINDOWPOS_CENTERED, /* Y       */
                                 SCREEN_WIDTH,           /* Width   */
                                 SCREEN_HEIGHT,          /* Height  */
                                 sdl_window_flags);      /* Flags   */

    GAME_VERIFY(g_pWindow, "SDL Cannot create window.");

    /* Renderer Initialization */
    g_pRenderer = SDL_CreateRenderer(g_pWindow,           /* The window     */
                                     -1,                  /* First Avaiable */
                                     sdl_renderer_flags); /* Flags          */

    GAME_VERIFY(g_pRenderer, "SDL Cannot create renderer.");

    scene_t game_scene;
    game_scene.id = 1;
    game_scene.load_func          = game_scene_load;
    game_scene.unload_func        = game_scene_unload;
    game_scene.update_func        = game_scene_update;
    game_scene.draw_func          = game_scene_draw;
    game_scene.handle_event_func  = game_scene_handle_event;

    game_add_scene(game_scene);
    game_change_to_scene(1);
}

void game_run()
{
    GAME_LOG("Running game...");

    /* Constants */
    const int   kFPS        = 60;
    const float kDELAY_TIME = (1000.0f / kFPS);

    /* Framerate vars */
    Uint32 frame_start;
    Uint32 frame_time;

    /* Game Loop :D */
    g_isRunning = 1;
    while(g_isRunning)
    {
        frame_start = SDL_GetTicks();

        game_handle_events();
        game_update(1.0f / kDELAY_TIME);
        game_render();

        frame_time = SDL_GetTicks() - frame_start;

        if(frame_time < kDELAY_TIME)
        {
            int v = (Uint32)(kDELAY_TIME - frame_time);
            SDL_Delay(v);
        }
    }
}

void game_quit(void)
{
    GAME_LOG("Quiting game.");

    SDL_DestroyRenderer(g_pRenderer);
    SDL_DestroyWindow(g_pWindow);

    SDL_Quit();
}

/*******************************************************************************
* Scene Management                                                             *
*******************************************************************************/
void game_add_scene(scene_t scene)
{
    scenes_arr[scenes_arr_count] = scene;
    ++scenes_arr_count;
}

void game_change_to_scene(int scene_id)
{
    if(scenes_arr_count != 0)
    {
        (scenes_arr[scenes_curr_index]).unload_func();
    }

    scenes_curr_index = -1;
    for(int i = 0; i < scenes_arr_count; ++i)
    {
        if(scenes_arr[i].id == scene_id)
            scenes_curr_index = i;
    }

    GAME_VERIFY(scenes_curr_index != -1, "Scene id (%d) not found");
    (scenes_arr[scenes_curr_index]).load_func();
}

void game_remove_scene(int scene_id)
{
    //COWTODO: Implement.
}



/*******************************************************************************
* Private Function Implementations                                             *
*******************************************************************************/
void game_update(float dt)
{
    (scenes_arr[scenes_curr_index]).update_func(dt);
}

void game_render(void)
{
    SDL_SetRenderDrawColor(g_pRenderer, 255, 0, 255, 255);
    SDL_RenderClear(g_pRenderer);

    (scenes_arr[scenes_curr_index]).draw_func();
    SDL_RenderPresent(g_pRenderer);
}

void game_handle_events(void)
{
    static SDL_Event s_event;
    while(SDL_PollEvent(&s_event))
    {
        if(s_event.type == SDL_QUIT)
            g_isRunning = 0;

        (scenes_arr[scenes_curr_index]).handle_event_func(&s_event);
    }
}

