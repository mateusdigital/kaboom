//Header
#include "GameScene.h"

//Usings
USING_NS_GAMEKABOOM;


////////////////////////////////////////////////////////////////////////////////
// Load / Unload                                                              //
////////////////////////////////////////////////////////////////////////////////
void GameScene::load()
{
    m_score      = 0;
    m_turnNumber = 10;
    m_state      = State::GameOver;

    initBomber();
    initBombs ();
    initTexts ();
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
    if(m_state == State::Paused)
    {

    }
    else if(m_state == State::Playing)
    {

    }
    else if(m_state == State::Victory)
    {

    }
    else if(m_state == State::Defeat)
    {

    }
    else if(m_state == State::GameOver)
    {

    }

    m_pauseBlinkTimer.update(dt);

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

    m_pauseText.draw();
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

void GameScene::initTexts()
{
    const char * const kFontName = "nokiafc22.ttf";
    constexpr int kFontSize_PauseText = 100;
    constexpr float kClockInterval_PauseText = 0.5;

    //Pause Text
    m_pauseText.loadFont(kFontName, kFontSize_PauseText);
    m_pauseText.setString("Paused");
    m_pauseText.setForegroundColor(Lore::Color::White());
    m_pauseText.setBackgroundColor(Lore::Color::Black());
    m_pauseText.setPosition(Lore::Vector2(100, 100));

    m_pauseBlinkTimer.setInterval(kClockInterval_PauseText);
    m_pauseBlinkTimer.setRepeatCount(CoreClock::Clock::kRepeatForever);
    m_pauseBlinkTimer.setTickCallback([this](){
        auto i = SDL_GetTicks();
        COREGAME_DLOG(CoreGame::Log::Type::Debug1,
                      "ticks %d", i);

        auto visible = (m_pauseBlinkTimer.getTickCount() % 2 == 0);
        m_pauseText.setIsVisible(visible);
    });

    m_pauseBlinkTimer.start();
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
    auto reach   = COREGAME_CALLBACK_0(GameScene::onBombReachTarget,     this);

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


//Texts Helpers
void GameScene::updateScoreText()
{

}

void GameScene::updateTurnNumberText()
{

}


//Bomber / Bomb Callbacks
void GameScene::onBomberBombDropped(const Lore::Vector2 &pos)
{

    COREGAME_DLOG(CoreGame::Log::Type::Debug1,
                  "Bomber drop bomb at: %.2f %.2f",
                  pos.x, pos.y);

    int index = getFirstAvaiableBombIndex();
    m_bombsVec[index]->setPosition(pos);
    m_bombsVec[index]->startDropping(m_turnNumber);
}

void GameScene::onBomberAllBombsDropped()
{
    COREGAME_DLOG(CoreGame::Log::Type::Debug1,
                  "Bomber drop all bomb");
}

void GameScene::onBombExplodeFinished()
{
    COREGAME_DLOG(CoreGame::Log::Type::Debug1,
                  "Bomb explode finished");

    explodeNextBomb();
}

void GameScene::onBombReachTarget()
{
    COREGAME_DLOG(CoreGame::Log::Type::Debug1,
                  "Bomb reach target");

    m_bomber.stopDropBombs();
    m_bomber.makeWinTurn  ();

    stopAllBombs   ();
    explodeNextBomb();
}
