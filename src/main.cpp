
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
    auto winMgr    = Lore::WindowManager::instance();
    auto assetsMgr = Lore::AssetsManager::instance();
    auto gameMgr   = Lore::GameManager::instance  ();
    auto inputMgr  = Lore::InputManager::instance ();
    auto soundMgr  = Lore::SoundManager::instance ();

    winMgr->initialize("Lore Test",
                        600, 480,
                        600, 480,
                        0, 0);

    assetsMgr->initialize("./assets");
    inputMgr->initialize();
    soundMgr->initialize();

    gameMgr->initialize(0, 60);

    gameMgr->run(std::unique_ptr<Lore::Scene>(new GameScene()));

    winMgr->shutdown();
    gameMgr->shutdown();

    return 0;
}
