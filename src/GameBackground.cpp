//Header
#include "GameBackground.h"
//GameScene
#include "GameScene_Constants.h"

//Usings
USING_NS_GAMEKABOOM;


void GameBackground::draw()
{
    //COWTODO: Clean this up.
    auto winMgr   = Lore::WindowManager::instance();
    auto renderer = winMgr->getRenderer();

    SDL_Rect skyRect = {
                0,
                0,
                winMgr->getWindowWidth(),
                kSize_SkyHeight
             };

    SDL_Rect groundRect = {
                0,
                kSize_SkyHeight,
                winMgr->getWindowWidth(),
                winMgr->getWindowHeight() - kSize_SkyHeight
            };

    SDL_SetRenderDrawColor(renderer, 0x70, 0x92, 0xBE, 0xFF);
    SDL_RenderFillRect(renderer, &skyRect);

    SDL_SetRenderDrawColor(renderer, 0x52, 0x7E, 0x2D, 0xFF);
    SDL_RenderFillRect(renderer, &groundRect);
}
