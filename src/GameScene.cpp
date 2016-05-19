//Header
#include "GameScene.h"

//Usings
USING_NS_GAMEKABOOM;


// Load / Unload //
void GameScene::load()
{
    initBomber();
}

void GameScene::unload()
{
    //Empty...
}


// Update / Draw / Handle Events //
void GameScene::update(float dt)
{
    auto inputMgr = Lore::InputManager::instance();
    if(inputMgr->isKeyClick(SDL_SCANCODE_SPACE))
        m_bomber.startDropBombs();

    m_bomber.update(dt);
}

void GameScene::draw()
{
    m_bomber.draw();
}


// Private Methods //
//Init
void GameScene::initBomber()
{
    auto winW = Lore::WindowManager::instance()->getWindowWidth();

    //Position / Movement
    m_bomber.setInitialPosition(Lore::Vector2(100, 100));

    m_bomber.setMovementBounds(Lore::Vector2(   0, 100),
                               Lore::Vector2(winW, 100));

    //Callbacks
    auto bombDropped = COREGAME_CALLBACK_1(GameScene::onBomberBombDropped, this);
    m_bomber.setOnBombDroppedCallback(bombDropped);

    auto allBombsDropped = COREGAME_CALLBACK_0(GameScene::onBomberAllBombsDropped, this);
    m_bomber.setOnAllBombsDroppedCallback(allBombsDropped);
}

//Bomber Callbacks
void GameScene::onBomberBombDropped(const Lore::Vector2 &pos)
{
    cout << "Bomber drop bomb at " << pos.x << ", " << pos.y << endl;
}

void GameScene::onBomberAllBombsDropped()
{
    cout << "Bomber drop all bomb" << endl;
}
