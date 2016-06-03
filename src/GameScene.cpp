//Header
#include "GameScene.h"
//GameScene
#include "GameScene_Constants.h"

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

    return "INVALID";
}

bool _Helper_IsKeyClick(Lore::InputManager::KeyScanCodeType key)
{
    static auto inputMgr = Lore::InputManager::instance();
    return inputMgr->isKeyClick(key);
}


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
GameScene::~GameScene()
{
    KABOOM_DLOG("GameScene DTOR");
}


////////////////////////////////////////////////////////////////////////////////
// Load / Unload                                                              //
////////////////////////////////////////////////////////////////////////////////
void GameScene::load()
{
    m_score       = 0;
    m_turnNumber  = 1;
    m_state       = State::Defeat;

    initBomber();
    initPaddle();
    initBombs ();
    initTexts ();
    initSounds();
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
    m_background.draw();

    //Bomber
    m_bomber.draw();

    //Bombs
    m_bombManager.draw();

    //Paddle
    m_paddle.draw();

    //Texts.
    m_pauseText.draw();
    m_scoreText.draw();
    m_turnText.draw ();
}


////////////////////////////////////////////////////////////////////////////////
// Inits                                                                      //
////////////////////////////////////////////////////////////////////////////////
void GameScene::initBomber()
{
    auto winW = Lore::WindowManager::instance()->getWindowWidth();

    //Position / Movement
    m_bomber.setInitialPosition(winW / 2, kPos_Bomber);
    m_bomber.setMovementBounds (0, winW);

    //Callbacks
    auto bomb = COREGAME_CALLBACK_1(GameScene::onBomberBombDropped, this);
    m_bomber.setOnBombDroppedCallback(bomb);
}

void GameScene::initPaddle()
{
    auto winW = Lore::WindowManager::instance()->getWindowWidth();

    //Position / Movement
    m_paddle.setInitialPosition(winW / 2, kPos_Player);
    m_paddle.setMovementBounds (0, winW);
}

void GameScene::initBombs()
{
    auto winHeight = Lore::WindowManager::instance()->getWindowHeight();
    m_bombManager.setBombMovementBounds(winHeight);

    auto bombCaught     = COREGAME_CALLBACK_0(GameScene::onBombCaught,     this);
    auto allBombsCaught = COREGAME_CALLBACK_0(GameScene::onAllBombsCaught, this);
    m_bombManager.setOnBombCaughtCallback    (bombCaught);
    m_bombManager.setOnAllBombsCaughtCallback(allBombsCaught);

    auto bombReachTarget  = COREGAME_CALLBACK_0(GameScene::onBombReachTarget, this);
    m_bombManager.setOnBombReachTargetCallback(bombReachTarget);

    auto bombExplode      = COREGAME_CALLBACK_0(GameScene::onBombExplode,      this);
    auto allBombsExploded = COREGAME_CALLBACK_0(GameScene::onAllBombsExploded, this);
    m_bombManager.setOnBombExplodeCallback     (bombExplode);
    m_bombManager.setOnAllBombsExplodedCallback(allBombsExploded);
}

void GameScene::initTexts()
{
    auto winRect = Lore::WindowManager::instance()->getWindowRect();

    //Pause Text
    initHelper_Text(m_pauseText,
                    kFontName, kFontSize_PauseText,
                    "Paused",
                    Lore::ITransformable::OriginHelpers::Center(),
                    winRect.getCenter());
    m_pauseText.setIsVisible(false);

    //Score Text
    initHelper_Text(m_scoreText,
                    kFontName, kFontSize_ScoreText,
                    CoreGame::StringUtils::format(kStringFormat_Score, 0),
                    Lore::ITransformable::OriginHelpers::TopLeft(),
                    winRect.getTopLeft() + Lore::Vector2(kTextOffset));

    //Turn Text
    initHelper_Text(m_turnText,
                    kFontName, kFontSize_TurnText,
                    CoreGame::StringUtils::format(kStringFormat_Level, 0),
                    Lore::ITransformable::OriginHelpers::TopRight(),
                    winRect.getTopRight() +
                        Lore::Vector2(-kTextOffset, kTextOffset));


    //Pause Timer
    m_pauseBlinkTimer.setInterval(kClockInterval_PauseText);
    m_pauseBlinkTimer.setRepeatCount(CoreClock::Clock::kRepeatForever);
    m_pauseBlinkTimer.setTickCallback([this]() {
        auto visible = (m_pauseBlinkTimer.getTickCount() % 2 == 0);
        m_pauseText.setIsVisible(visible);
    });
    m_pauseBlinkTimer.start();


    updateScoreText     ();
    updateTurnNumberText();
}

void GameScene::initSounds()
{
    auto soundMgr = Lore::SoundManager::instance();

    soundMgr->loadEffect(kSoundName_LevelStart);
    soundMgr->loadEffect(kSoundName_Victory   );
    soundMgr->loadEffect(kSoundName_Defeat    );
    soundMgr->loadEffect(kSoundName_GameOver  );
}


////////////////////////////////////////////////////////////////////////////////
// Texts Helpers                                                              //
////////////////////////////////////////////////////////////////////////////////
void GameScene::updateScoreText()
{
    m_scoreText.setString(kStringFormat_Score, m_score * kScoreMutilplier);
}

void GameScene::updateTurnNumberText()
{
    m_turnText.setString(kStringFormat_Level, m_turnNumber);
}


////////////////////////////////////////////////////////////////////////////////
//  Bomber / Bomb Callbacks                                                   //
////////////////////////////////////////////////////////////////////////////////
//Bomber
void GameScene::onBomberBombDropped(const Lore::Vector2 &pos)
{
    KABOOM_DLOG("Bomber drop bomb at: %.2f %.2f", pos.x, pos.y);
    m_bombManager.dropBombAt(pos);
}

//Bombs
void GameScene::onBombCaught()
{
    KABOOM_DLOG("GameScene::onBombCaught");

    ++m_score;
    updateScoreText();
}

void GameScene::onAllBombsCaught()
{
    KABOOM_DLOG("GameScene::onAllBombsCaught");

    m_bomber.makeLoseTurn();
    gameStateHelper_PlayingToVictory();
}


void GameScene::onBombReachTarget()
{
    KABOOM_DLOG("GameScene::onBombReachTarget");

    m_bomber.makeWinTurn  ();
    m_bomber.stopDropBombs();
}


void GameScene::onBombExplode()
{
    KABOOM_DLOG("GameScene::onBombExplode");
    m_background.explode();
}

void GameScene::onAllBombsExploded()
{
    KABOOM_DLOG("GameScene::onAllBombsExploded");
    m_background.setNormalColor();

    m_paddle.kill();
    gameStateHelper_PlayingToDefeat();
}


////////////////////////////////////////////////////////////////////////////////
// Others                                                                     //
////////////////////////////////////////////////////////////////////////////////
void GameScene::resetTurn()
{
    KABOOM_DLOG("Reset turn:\n\t Current Turn: %d", m_turnNumber);

    updateTurnNumberText();

    //COWTODO: Create this correctly.
    TurnInfo turnInfo {
        .turnNumber  = m_turnNumber,
        .bombsCount  =   5 + (m_turnNumber *  5),
        .bombSpeed   = 200 + (m_turnNumber * 10),
        .bomberSpeed = 200 + (m_turnNumber * 20),
    };

    //Reset the game objects for this level.
    m_bombManager.reset(turnInfo);
    m_bomber.reset     (turnInfo);

    //Make bomber drop bombs.
    m_bomber.startDropBombs();
}

void GameScene::resetNewTurn()
{
    ++m_turnNumber;
    resetTurn();
}

void GameScene::checkCollisions()
{
    m_bombManager.checkCollision(m_paddle);
}


////////////////////////////////////////////////////////////////////////////////
// Game State Update Helpers                                                  //
////////////////////////////////////////////////////////////////////////////////
void GameScene::updateHelper_Playing(float dt)
{
    //Input.
    if(_Helper_IsKeyClick(SDL_SCANCODE_P))
    {
        gameStateHelper_PlayingToPaused();
        return;
    }

    //Update the Game Objects.
    m_paddle.update     (dt);
    m_bomber.update     (dt);
    m_bombManager.update(dt);

    //Collisions.
    checkCollisions();
}

void GameScene::updateHelper_Paused(float dt)
{
    //Input.
    if(_Helper_IsKeyClick(SDL_SCANCODE_P))
    {
        gameStateHelper_PausedToPlaying();
        return;
    }

    m_pauseBlinkTimer.update(dt);
}

void GameScene::updateHelper_Victory(float dt)
{
    //Input.
    if(_Helper_IsKeyClick(SDL_SCANCODE_SPACE))
    {
        gameStateHelper_VictoryToPlaying();
        return;
    }

    //Let the paddle move in victory too.
    m_paddle.update(dt);
}

void GameScene::updateHelper_Defeat(float dt)
{
    //Input.
    if(_Helper_IsKeyClick(SDL_SCANCODE_SPACE))
    {
        gameStateHelper_DefeatToPlaying();
        return;
    }

    //Let the paddle move in defeat too.
    m_paddle.update(dt);
}

void GameScene::updateHelper_GameOver(float dt)
{
    //Input.
    if(_Helper_IsKeyClick(SDL_SCANCODE_SPACE))
    {
        gameStateHelper_GameOverToPlaying();
        return;
    }
}


////////////////////////////////////////////////////////////////////////////////
// Init Helpers                                                               //
////////////////////////////////////////////////////////////////////////////////
void GameScene::initHelper_Text(Lore::Text &text,
                                const std::string   &fontName, int fontSize,
                                const std::string   &str,
                                const Lore::Vector2 &origin,
                                const Lore::Vector2 &position)
{
    text.loadFont          (fontName, fontSize);
    text.setString         (str);
    text.setForegroundColor(Lore::Color::White());
    text.setOrigin         (origin);
    text.setPosition       (position);
}


////////////////////////////////////////////////////////////////////////////////
// Sound Helpers                                                              //
////////////////////////////////////////////////////////////////////////////////
void GameScene::soundHelper_Play(const std::string &name)
{
    Lore::SoundManager::instance()->playEffect(name);
}

void GameScene::soundHelper_Stop(const std::string &name)
{
    Lore::SoundManager::instance()->stopEffect(name);
}

void GameScene::soundHelper_Unmute()
{
    Lore::SoundManager::instance()->setEffectsVolume(0);
}

void GameScene::soundHelper_Mute()
{
    Lore::SoundManager::instance()->setEffectsVolume(1);
}


////////////////////////////////////////////////////////////////////////////////
// Game State Helpers                                                         //
////////////////////////////////////////////////////////////////////////////////
//Playing / Paused
void GameScene::gameStateHelper_PlayingToPaused()
{
    KABOOM_DLOG("GameScene::gameStateHelper_PlayingToPaused");

    soundHelper_Unmute();

    m_pauseBlinkTimer.start();
    m_pauseText.setIsVisible(true);

    m_state = GameScene::State::Paused;
}

void GameScene::gameStateHelper_PausedToPlaying()
{
    KABOOM_DLOG("GameScene::gameStateHelper_PausedToPlaying");

    soundHelper_Mute();

    m_pauseBlinkTimer.stop();
    m_pauseText.setIsVisible(false);

    m_state = GameScene::State::Playing;
}


//Playing / Defeat
void GameScene::gameStateHelper_PlayingToDefeat()
{
    KABOOM_DLOG("GameScene::gameStateHelper_PlayingToDefeat");

    soundHelper_Play(kSoundName_Defeat);

    m_state = GameScene::State::Defeat;
}

void GameScene::gameStateHelper_DefeatToPlaying()
{
    KABOOM_DLOG("GameScene::gameStateHelper_DefeatToPlaying");

    soundHelper_Play(kSoundName_LevelStart);

    resetTurn();
    m_state = GameScene::State::Playing;
}


//Playing / Victory
void GameScene::gameStateHelper_PlayingToVictory()
{
    KABOOM_DLOG("GameScene::gameStateHelper_PlayingToVictory");

    soundHelper_Play(kSoundName_Victory);
    m_state = GameScene::State::Victory;
}

void GameScene::gameStateHelper_VictoryToPlaying()
{
    KABOOM_DLOG("GameScene::gameStateHelper_VictoryToPlaying");

    soundHelper_Play(kSoundName_LevelStart);

    resetNewTurn();
    m_state = GameScene::State::Playing;
}


//Playing / GameOver
void GameScene::gameStateHelper_PlayingToGameOver()
{

}

void GameScene::gameStateHelper_GameOverToPlaying()
{

}
