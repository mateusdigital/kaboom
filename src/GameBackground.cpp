//Header
#include "GameBackground.h"
//GameScene
#include "GameScene_Constants.h"

//Usings
USING_NS_GAMEKABOOM;

// CTOR / DTOR //
GameBackground::GameBackground()
{
    setNormalColor();
}

// Public Methods //
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


    SDL_SetRenderDrawColor(renderer, m_skyColor.r,
                                     m_skyColor.g,
                                     m_skyColor.b,
                                     m_skyColor.a);
    SDL_RenderFillRect(renderer, &skyRect);

    SDL_SetRenderDrawColor(renderer, m_groundColor.r,
                                     m_groundColor.g,
                                     m_groundColor.b,
                                     m_groundColor.a);
    SDL_RenderFillRect(renderer, &groundRect);
}

void GameBackground::explode()
{
    auto gm = Lore::GameManager::instance();

    m_skyColor.setRGBA(gm->getRandomNumber(0, 255),
                       gm->getRandomNumber(0, 255),
                       gm->getRandomNumber(0, 255));

    m_groundColor.setRGBA(gm->getRandomNumber(0, 255),
                          gm->getRandomNumber(0, 255),
                          gm->getRandomNumber(0, 255));
}

void GameBackground::setNormalColor()
{
    m_skyColor.setRGBA   (0x70, 0x92, 0xBE);
    m_groundColor.setRGBA(0x52, 0x7E, 0x2D);
}
