#ifndef __Game_Kaboom_include_game_h__
#define __Game_Kaboom_include_game_h__

/* SDL */
#include <SDL2/SDL.h>
/* Game_Kaboom */
#include "scene.h"

/*******************************************************************************
* Constants                                                                    *
*******************************************************************************/
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;


/*******************************************************************************
* Globals                                                                      *
*******************************************************************************/
extern SDL_Window   *g_pWindow;
extern SDL_Renderer *g_pRenderer;
extern int           g_isRunning;


/*******************************************************************************
* Game Lifecycle                                                               *
*******************************************************************************/
void game_init(const char *window_name,
               int sdl_window_flags,
               int sdl_renderer_flags);

void game_run(void);
void game_quit(void);


/*******************************************************************************
* Scene Management                                                             *
*******************************************************************************/
void game_add_scene(scene_t scene);
void game_change_to_scene(int scene_id);
void game_remove_scene(int scene_id);


#endif /* defined(__Game_Kaboom_include_game_h__) */
