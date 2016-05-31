//Header
#include "GameScene.h"

//Usings
USING_NS_GAMEKABOOM;


////////////////////////////////////////////////////////////////////////////////
// Helper Functions                                                           //
////////////////////////////////////////////////////////////////////////////////
std::string _Helper_GetStateName(GameScene::State state)
{
    switch(state)
    {
        case GameScene::State::Playing  : return "Playing" ;
        case GameScene::State::Paused   : return "Paused"  ;
        case GameScene::State::Victory  : return "Victory" ;
        case GameScene::State::Defeat   : return "Defeat"  ;
        case GameScene::State::GameOver : return "GameOver";
    }
}


////////////////////////////////////////////////////////////////////////////////
// Constants                                                                  //
////////////////////////////////////////////////////////////////////////////////
// Text //
const char * const kFontName = "nokiafc22.ttf";

constexpr int kFontSize_PauseText = 100;
constexpr int kFontSize_ScoreText = 20;
constexpr int kFontSize_TurnText  = 20;
constexpr int kTextOffset         = 20;

// Timers //
constexpr float kClockInterval_PauseText = 0.5; //Half a second.

// Positions / Sizes //
constexpr int kSize_SkyHeight = 150;
constexpr int kPos_Bomber     = kSize_SkyHeight;
constexpr int kPos_Player     = 400;

//Score
constexpr int kScoreMutilplier = 50;


////////////////////////////////////////////////////////////////////////////////
// Load / Unload                                                              //
////////////////////////////////////////////////////////////////////////////////
void GameScene::load()
{
    m_score       = 0;
    m_turnNumber  = 10;
    m_state       = State::Defeat;
    m_bombsCaught = 0 ;

    initBomber();
    initPaddle();
    initBombs ();
    initTexts ();
}

void GameScene::unload()
{
    //Empty...
}


////////////////////////////////////////////////////////////////////////////////
// Update / Draw                                                              //
////////////////////////////////////////////////////////////////////////////////
void GameScene::update(float dt)
{
    switch(m_state)
    {
        case State::Playing  : updateHelper_Playing (dt); break;
        case State::Paused   : updateHelper_Paused  (dt); break;
        case State::Victory  : updateHelper_Victory (dt); break;
        case State::Defeat   : updateHelper_Defeat  (dt); break;
        case State::GameOver : updateHelper_GameOver(dt); break;
    }
}

void GameScene::draw()
{
    //Background
    drawBackgroundHelper();

    //Bomber
    m_bomber.draw();

    //Bombs
    for(auto &bomb : m_bombsVec)
        bomb->draw();

    //Paddle
    m_paddle.draw();

    //Texts.
    m_pauseText.draw();
    m_scoreText.draw();
    m_turnText.draw ();
}


////////////////////////////////////////////////////////////////////////////////
// Private Methods                                                            //
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Inits                                                                      //
////////////////////////////////////////////////////////////////////////////////
void GameScene::initBomber()
{
    auto winW = Lore::WindowManager::instance()->getWindowWidth();

    //Position / Movement
    m_bomber.setInitialPosition(Lore::Vector2(winW / 2, //Center
                                              kPos_Bomber));

    m_bomber.setMovementBounds(Lore::Vector2(   0, 0 /*Y is indifferent */),
                               Lore::Vector2(winW, 0 /*Y is indifferent */));

    //Callbacks
    auto bomb = COREGAME_CALLBACK_1(GameScene::onBomberBombDropped, this);
    m_bomber.setOnBombDroppedCallback(bomb);

    auto allBombs = COREGAME_CALLBACK_0(GameScene::onBomberAllBombsDropped, this);
    m_bomber.setOnAllBombsDroppedCallback(allBombs);
}

void GameScene::initPaddle()
{
    auto winW = Lore::WindowManager::instance()->getWindowWidth();

    //Position / Movement
    m_paddle.setInitialPosition(Lore::Vector2(winW / 2, //Center
                                              kPos_Player));

    m_paddle.setMovementBounds(Lore::Vector2(   0, 0 /*Y is indifferent */),
                               Lore::Vector2(winW, 0 /*Y is indifferent */));
}

void GameScene::initBombs()
{
    for(int i = 0; i < 10; ++i)
        createBombHelper();
}

void GameScene::initTexts()
{
    auto winRect = Lore::WindowManager::instance()->getWindowRect();

    //Pause Text
    m_pauseText.loadFont(kFontName, kFontSize_PauseText);
    m_pauseText.setString("Paused");
    m_pauseText.setForegroundColor(Lore::Color::White());
    m_pauseText.setBackgroundColor(Lore::Color::Black());
    m_pauseText.setOrigin(Lore::ITransformable::OriginHelpers::Center());
    m_pauseText.setPosition(winRect.getCenter());
    m_pauseText.setIsVisible(false);

    //Pause Timer
    m_pauseBlinkTimer.setInterval(kClockInterval_PauseText);
    m_pauseBlinkTimer.setRepeatCount(CoreClock::Clock::kRepeatForever);
    m_pauseBlinkTimer.setTickCallback([this]() {
        auto visible = (m_pauseBlinkTimer.getTickCount() % 2 == 0);
        m_pauseText.setIsVisible(visible);
    });
    m_pauseBlinkTimer.start();

    //Score Text
    m_scoreText.loadFont(kFontName, kFontSize_ScoreText);
    m_scoreText.setString("Score: 0000");
    m_scoreText.setForegroundColor(Lore::Color::White());
    m_scoreText.setPosition(winRect.getTopLeft() +
                            Lore::Vector2(kTextOffset));

    //Turn Text
    m_turnText.loadFont(kFontName, kFontSize_TurnText);
    m_turnText.setString("Level: 01");
    m_turnText.setForegroundColor(Lore::Color::White());
    m_turnText.setOrigin(Lore::ITransformable::OriginHelpers::TopRight());
    m_turnText.setPosition(winRect.getTopRight() +
                           Lore::Vector2(-kTextOffset, kTextOffset));
}


////////////////////////////////////////////////////////////////////////////////
// Bomb Helpers                                                               //
////////////////////////////////////////////////////////////////////////////////
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

bool GameScene::explodeNextBomb()
{
    //Keep search for an alive bomb and explode it.
    for(auto &bomb : m_bombsVec)
    {
        if(bomb->getState() == Bomb::State::Alive)
        {
            bomb->explode();
            return true; //Could explode a bomb.
        }
    }

    //No bombs was exploded - Means that all bombs
    //were already exploded.
    return false;
}

////////////////////////////////////////////////////////////////////////////////
// Texts Helpers                                                              //
////////////////////////////////////////////////////////////////////////////////
void GameScene::updateScoreText()
{
    m_scoreText.setString("Score: %05d", m_score * kScoreMutilplier);
}

void GameScene::updateTurnNumberText()
{
    m_turnText.setString("Level: %02d", m_turnNumber);
}


////////////////////////////////////////////////////////////////////////////////
//  Bomber / Bomb Callbacks                                                   //
////////////////////////////////////////////////////////////////////////////////
//Bomber
void GameScene::onBomberBombDropped(const Lore::Vector2 &pos)
{
    KABOOM_DLOG("Bomber drop bomb at: %.2f %.2f", pos.x, pos.y);

    int index = getFirstAvaiableBombIndex();
    m_bombsVec[index]->setPosition(pos);
    m_bombsVec[index]->startDropping(m_turnNumber);
}

void GameScene::onBomberAllBombsDropped()
{
    KABOOM_DLOG("Bomber drop all bomb");
}

//Bomb
void GameScene::onBombExplodeFinished()
{
    KABOOM_DLOG("Bomb explode finished - Player has %d lives",
                m_paddle.getLives());

    if(!explodeNextBomb())
    {
        //Kill one of player paddles.
        m_paddle.kill();

        if(m_paddle.getLives() != 0)
        {
            KABOOM_DLOG("Changing state to Defeat");
            changeState(State::Defeat);
        }
        else
        {
            KABOOM_DLOG("Changing state to GameOver");
            changeState(State::GameOver);
        }
    }
}

void GameScene::onBombReachTarget()
{
    KABOOM_DLOG("Bomb reach target");

    //Bomber
    m_bomber.stopDropBombs();
    m_bomber.makeWinTurn  ();

    //Bombs
    stopAllBombs   ();
    explodeNextBomb();
}


////////////////////////////////////////////////////////////////////////////////
// Others                                                                     //
////////////////////////////////////////////////////////////////////////////////
void GameScene::changeState(State state)
{
    KABOOM_DLOG("-- CHANGE STATE -- \nFrom %s\nTo:%s",
                _Helper_GetStateName(m_state).c_str(),
                _Helper_GetStateName(state  ).c_str());
    m_state = state;
}

void GameScene::resetTurn()
{
    KABOOM_DLOG("Reset turn:\n\t Current Turn: %d", m_turnNumber);

    //
    m_bombsCaught = 0;
    resetAllBombs();
    m_bomber.startDropBombs(m_turnNumber);
}

void GameScene::resetNewTurn()
{
    using namespace CoreGame;
    KABOOM_DLOG("Reset new turn:\n\t %s\n\t %s",
                StringUtils::format("Current Turn: %d", m_turnNumber).c_str(),
                StringUtils::format("Next Turn: %d", m_turnNumber + 1).c_str()
    );

    ++m_turnNumber;

    m_bombsCaught = 0;
    resetAllBombs();
    m_bomber.startDropBombs(m_turnNumber);

    updateTurnNumberText();
}


////////////////////////////////////////////////////////////////////////////////
// Game State Update Helpers                                                  //
////////////////////////////////////////////////////////////////////////////////
void GameScene::updateHelper_Playing(float dt)
{
    //Input.
    auto inputMgr = Lore::InputManager::instance();
    if(inputMgr->isKeyClick(SDL_SCANCODE_P))
    {
        KABOOM_DLOG("Changing state to Paused");

        m_pauseText.setIsVisible(false);
        changeState(GameScene::State::Paused);

        return;
    }

    //Paddle
    m_paddle.update(dt);

    //Bomber
    m_bomber.update(dt);

    //Bombs
    for(auto &bomb : m_bombsVec)
        bomb->update(dt);

    //Check collisions.
    for(auto &bomb : m_bombsVec)
    {
        //We don't care for non alive bombs...
        if(bomb->getState() != Bomb::State::Alive)
            continue;

        if(m_paddle.checkCollision(bomb->getHitBox()))
        {
            bomb->kill();

            //Update the HouseKeeping vars..
            ++m_bombsCaught;
            ++m_score;

            //Log
            KABOOM_DLOG("Bombs caught count: %d - Total Bombs count %d",
                        m_bombsCaught, m_bomber.getTurnBombsCount());

            //Update the Score Text
            updateScoreText();

            //Check if Player won this level.
            if(m_bombsCaught == m_bomber.getTurnBombsCount())
            {
                KABOOM_DLOG("All bombs were caught - Changing to state Victory");

                m_bomber.makeLoseTurn();
                changeState(State::Victory);
            }

        }//if(m_paddle.checkCollision...)

    }//for(auto &bomb : m_bombs)
}//updateHelper_Playing

void GameScene::updateHelper_Paused(float dt)
{
    //Input.
    auto inputMgr = Lore::InputManager::instance();
    if(inputMgr->isKeyClick(SDL_SCANCODE_P))
    {
        KABOOM_DLOG("Changing state to Playing");

        m_pauseText.setIsVisible(true);
        changeState(GameScene::State::Playing);

        return;
    }

    m_pauseBlinkTimer.update(dt);
}

void GameScene::updateHelper_Victory(float dt)
{
    //Input.
    auto inputMgr = Lore::InputManager::instance();
    if(inputMgr->isKeyClick(SDL_SCANCODE_SPACE))
    {
        KABOOM_DLOG("Changing state to Playing");

        resetNewTurn();
        changeState(GameScene::State::Playing);

        return;
    }

    //Paddle
    m_paddle.update(dt);
}

void GameScene::updateHelper_Defeat(float dt)
{
    //Input.
    auto inputMgr = Lore::InputManager::instance();
    if(inputMgr->isKeyClick(SDL_SCANCODE_SPACE))
    {
        KABOOM_DLOG("Changing state to Playing");

        resetTurn();
        changeState(GameScene::State::Playing);

        return;
    }
}

void GameScene::updateHelper_GameOver(float dt)
{

}


////////////////////////////////////////////////////////////////////////////////
// Draw Helpers                                                               //
////////////////////////////////////////////////////////////////////////////////
//Background
void GameScene::drawBackgroundHelper()
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
