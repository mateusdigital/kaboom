
/* Game_Kaboom */
#include "game.h"

/* Game Init */
int main(int argc, char* args[])
{
    game_init("Amazing Cow - Kaboom - v0.1",
              SDL_WINDOW_SHOWN,
              SDL_RENDERER_ACCELERATED);

    game_run();
    game_quit();

    return 0;
}
