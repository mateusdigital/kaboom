
//Lore
#include "Lore.h"
//Game_Kaboom
#include "GameKaboom_Utils.h"
#include "MenuScene.h"
#include "GameScene.h"

//Usings
USING_NS_GAMEKABOOM;


int main()
{
    Lore::ErrorControl::DieMode = Lore::ErrorControl::LORE_ERROR_DIE_ON_ALL_ERRORS;

    auto winMgr    = Lore::WindowManager::instance();
    auto assetsMgr = Lore::AssetsManager::instance();
    auto gameMgr   = Lore::GameManager::instance  ();
    auto inputMgr  = Lore::InputManager::instance ();
    auto soundMgr  = Lore::SoundManager::instance ();

    winMgr->initialize("Lore Test",
                        800, 600,
                        800, 600,
                        0, 0);

    assetsMgr->initialize("./assets");
    inputMgr->initialize();
    soundMgr->initialize("./assets",
                         MIX_DEFAULT_FREQUENCY,
                         MIX_DEFAULT_FORMAT,
                         MIX_DEFAULT_CHANNELS,
                         2048);

    gameMgr->initialize(0, 60);

    gameMgr->run(std::unique_ptr<Lore::Scene>(new GameScene()));

    winMgr->shutdown();
    gameMgr->shutdown();

    return 0;
}
