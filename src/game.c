/* Header */
#include "game.h"
/* Game_Kaboom */
#include "helpers.h"

/* Screen dimension constants */
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

/* Globals */
SDL_Window   *g_pWindow   = NULL;
SDL_Renderer *g_pRenderer = NULL;
bool         *g_isRunning = false;



/* Private Function Prototypes */
void game_update(float dt);
void game_render(void);
void game_handle_events(void);


/* Public Functions Implementation */
bool game_init(const char *window_name,
               int sdl_window_flags,
               int sdl_renderer_flags)
{
    GAME_LOG("Initializing SDL.");

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    g_pWindow = SDL_CreateWindow(window_name,
                                 SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED,
                                 SCREEN_WIDTH,
                                 SCREEN_HEIGHT,
                                 sdl_window_flags);

    g_pRenderer = SDL_CreateRenderer(g_pWindow,
                                   -1,
                                   sdl_renderer_flags);
}


void game_run()
{
    GAME_LOG("Running game.");

    g_isRunning = true;
    while(g_isRunning)
    {
        game_handle_events();
        game_update(0.6);
        game_render();


        SDL_Delay(100);
    }
}

void game_quit(void)
{
    GAME_LOG("Quiting game.");
    SDL_DestroyRenderer(g_pRenderer);
    SDL_DestroyWindow(g_pWindow);

    SDL_Quit();
}


/* Private Function Prototypes */
void game_update(float dt)
{
}
void game_render(void)
{
    SDL_SetRenderDrawColor(g_pRenderer, 255, 0, 255, 255);
    SDL_RenderClear(g_pRenderer);
    SDL_RenderPresent(g_pRenderer);
}
void game_handle_events(void)
{
    static SDL_Event s_event;
    while(SDL_PollEvent(&s_event))
    {
        if(s_event.type == SDL_QUIT)
            g_isRunning = false;
    }
}
