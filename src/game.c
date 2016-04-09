/* Header */
#include "game.h"
/* Game_Kaboom */
#include "helpers.h"
#include "game_textures.h"

/*******************************************************************************
* Screen dimension constants                                                   *
*******************************************************************************/
const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 600;


/*******************************************************************************
* Globals                                                                      *
*******************************************************************************/
/* Public */
SDL_Window   *g_pWindow   = NULL;
SDL_Renderer *g_pRenderer = NULL;
bool          g_isRunning = false;
/* Private */
SDL_Texture* g_textures_arr[GAME_TEXTURES_IDS_SIZE] = { NULL };


/*******************************************************************************
* Private Function Prototypes                                                  *
*******************************************************************************/
void game_update       (float dt);
void game_render       (void    );
void game_handle_events(void    );


/*******************************************************************************
* Public Function Implementations                                              *
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
    g_isRunning = true;
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


/* Textures Stuff */
SDL_Texture* game_load_texture(int texture_id)
{
    /* Already loaded - Just returns... */
    if(g_textures_arr[texture_id])
        return g_textures_arr[texture_id];

    /* Texture isn't loaded yet - Load it and save to the textures array */
    SDL_Surface *tmp_surface = SDL_LoadBMP(game_textures_ids[texture_id]);
    GAME_VERIFY(tmp_surface,
                "Cannot create surface with filename: %s",
                game_textures_ids[texture_id]);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(g_pRenderer, tmp_surface);
    GAME_VERIFY(texture,
                "Failed to create texture from surface with filename: %s",
                game_textures_ids[texture_id]);

    /* Prevent leak */
    SDL_FreeSurface(tmp_surface);

    g_textures_arr[texture_id] = texture;

    return texture;
}
void game_unload_texture(int texture_id)
{
    /* COWTODO: Implement... */
}

void game_draw_texture(SDL_Texture *texture,
                       int x, int y,
                       int w, int h,
                       SDL_RendererFlip flip)
{
    SDL_Rect src_rect = {0, 0, w, h};
    SDL_Rect dst_rect = {x, y, w, h};

    SDL_RenderCopyEx(g_pRenderer,
                     texture,
                     &src_rect, &dst_rect,
                     0, 0,
                     flip);
}


/*******************************************************************************
* Private Function Implementations                                             *
*******************************************************************************/
void game_update(float dt)
{
/*
    Uint8 *k = SDL_GetKeyboardState(0);

    if(k[SDL_SCANCODE_LEFT])
    if(k[SDL_SCANCODE_RIGHT])
*/
}
void game_render(void)
{
    SDL_SetRenderDrawColor(g_pRenderer, 255, 0, 255, 255);
    SDL_RenderClear(g_pRenderer);


    /*
    game_draw_texture(g_textures_arr[game_texture_id_ballon],
                      x, 100,
                      40, 40,
                      SDL_FLIP_NONE);
    */
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
