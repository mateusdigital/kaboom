#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

/* std */
#include <stdio.h>
/* SDL */
#include <SDL2/SDL.h>
/* Game_Kaboom */
#include "game_types.h"

/*******************************************************************************
* Screen dimension constants                                                   *
*******************************************************************************/
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;


/*******************************************************************************
* Globals                                                                      *
*******************************************************************************/
extern SDL_Window   *g_pWindow;
extern SDL_Renderer *g_pRenderer;
extern bool          g_isRunning;


/*******************************************************************************
* Public Function Prototypes                                                   *
*******************************************************************************/
/* Game loop */
void game_init(const char *window_name,
               int sdl_window_flags,
               int sdl_renderer_flags);

void game_run(void);
void game_quit(void);

/* Texture Stuff */
SDL_Texture* game_load_texture(int texture_id);
void game_unload_texture(int texture_id);


#endif /* defined(GAME_H_INCLUDED) */
