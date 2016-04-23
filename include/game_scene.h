#ifndef __Game_Kaboom_include_game_scene_h__
#define __Game_Kaboom_include_game_scene_h__

/* SDL */
#include <SDL2/SDL.h>

/*******************************************************************************
* Public Functions                                                             *
*******************************************************************************/
void game_scene_load  (void);
void game_scene_unload(void);
void game_scene_update(float dt);
void game_scene_draw  (void);
void game_scene_handle_event(SDL_Event *event);


#endif // __Game_Kaboom_include_game_scene_h__
