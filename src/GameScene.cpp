//Header
#include "GameScene.h"

//Usings
USING_NS_GAMEKABOOM;

////////////////////////////////////////////////////////////////////////////////
// Load / Unload                                                              //
////////////////////////////////////////////////////////////////////////////////
void GameScene::load()
{
    m_turnNumber = 10;

    initBomber();
    initBombs ();
}

void GameScene::unload()
{
    //Empty...
}


////////////////////////////////////////////////////////////////////////////////
// Update / Draw / Handle Events                                              //
////////////////////////////////////////////////////////////////////////////////
void GameScene::update(float dt)
{
    auto inputMgr = Lore::InputManager::instance();
    if(inputMgr->isKeyClick(SDL_SCANCODE_SPACE))
        m_bomber.startDropBombs(m_turnNumber);

    //Bomber
    m_bomber.update(dt);
    //Bombs
    for(auto &bomb : m_bombsVec)
        bomb->update(dt);
}

void GameScene::draw()
{
    //Bomber
    m_bomber.draw();
    //Bombs
    for(auto &bomb : m_bombsVec)
        bomb->draw();
}


////////////////////////////////////////////////////////////////////////////////
// Private Methods                                                            //
////////////////////////////////////////////////////////////////////////////////
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

void GameScene::initBombs()
{
    for(int i = 0; i < 10; ++i)
        createBombHelper();
}

//Bomb Helpers
void GameScene::resetAllBombs()
{
    for(auto &bomb : m_bombsVec)
        bomb->reset();
}

void GameScene::stopAllBombs()
{
    for(auto &bomb : m_bombsVec)
        bomb->stopDropping();
}

int GameScene::getFirstAvaiableBombIndex()
{
    for(int i = 0; i < m_bombsVec.size(); ++i)
    {
        if(m_bombsVec[i]->getState() == Bomb::State::Dead)
            return i;
    }

    createBombHelper();
    return m_bombsVec.size() -1;
}

void GameScene::createBombHelper()
{
    auto winH = Lore::WindowManager::instance()->getWindowHeight();
    auto bomb = std::unique_ptr<Bomb>(new Bomb());

    auto explode = COREGAME_CALLBACK_0(GameScene::onBombExplodeFinished, this);
    auto reach   = COREGAME_CALLBACK_0(GameScene::onBombReachTarget,    this);

    bomb->setMovementBounds(Lore::Vector2(0, winH));

    bomb->setOnReachTargetCallback    (reach);
    bomb->setOnExplodeFinishedCallback(explode);

    m_bombsVec.push_back(std::move(bomb));
}

void GameScene::explodeNextBomb()
{
    bool exploded = false;
    for(auto &bomb : m_bombsVec)
    {
        if(bomb->getState() == Bomb::State::Alive)
        {
            bomb->explode();
            exploded = true;
            break;
        }
    }
}

//Bomber / Bomb Callbacks
void GameScene::onBomberBombDropped(const Lore::Vector2 &pos)
{
    cout << "Bomber drop bomb at " << pos.x << ", " << pos.y << endl;

    int index = getFirstAvaiableBombIndex();
    m_bombsVec[index]->setPosition(pos);
    m_bombsVec[index]->startDropping(m_turnNumber);
}

void GameScene::onBomberAllBombsDropped()
{
    cout << "Bomber drop all bomb" << endl;
}

void GameScene::onBombExplodeFinished()
{
    cout << "Bomb explode finished" << endl;
    explodeNextBomb();
}

void GameScene::onBombReachTarget()
{
    cout << "Bomb reach target" << endl;

    m_bomber.stopDropBombs();

    stopAllBombs   ();
    explodeNextBomb();
}

