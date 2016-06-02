#ifndef __Game_Kaboom_include_GameScene_h__
#define __Game_Kaboom_include_GameScene_h__

//Game_Kaboom
#include "GameKaboom_Utils.h"
#include "Bomber.h"
#include "BombManager.h"
#include "GameBackground.h"
#include "Paddle.h"


NS_GAMEKABOOM_BEGIN

class GameScene : public Lore::Scene
{
    // Enums //
public:
    enum class State
    {
        Playing,
        Paused,
        Victory,
        Defeat,
        GameOver
    };


    // CTOR / DTOR //
public:
    virtual ~GameScene();


    // Load / Unload //
public:
    virtual void load  () override;
    virtual void unload() override;


    // Update / Draw //
public:
    virtual void update(float dt) override;
    virtual void draw()           override;


    // Inits //
private:
    void initBomber();
    void initPaddle();
    void initBombs ();
    void initTexts ();
    void initSounds();


    // Texts Helpers //
private:
    void updateScoreText     ();
    void updateTurnNumberText();


    // Bomber / Bomb Manager Callbacks //
private:
    //Bomber
    void onBomberBombDropped(const Lore::Vector2 &pos);

    //Bombs
    void onBombCaught    ();
    void onAllBombsCaught();

    void onBombReachTarget();

    void onBombExplode     ();
    void onAllBombsExploded();


    // Others //
private:
    void resetTurn   ();
    void resetNewTurn();

    void checkCollisions();


    // Update Helpers //
private:
    void updateHelper_Playing (float dt);
    void updateHelper_Paused  (float dt);
    void updateHelper_Victory (float dt);
    void updateHelper_Defeat  (float dt);
    void updateHelper_GameOver(float dt);


    // Init Helpers //
private:
    void initHelper_Text(Lore::Text &text,
                         const std::string   &fontName, int fontSize,
                         const std::string   &str,
                         const Lore::Vector2 &origin,
                         const Lore::Vector2 &position);


    // Sound Helpers //
private:
    void soundHelper_Play(const std::string &name);
    void soundHelper_Stop(const std::string &name);
    void soundHelper_Unmute();
    void soundHelper_Mute  ();


    // Game State Helpers //
private:
    //Playing / Paused
    void gameStateHelper_PlayingToPaused();
    void gameStateHelper_PausedToPlaying();

    //Playing / Defeat
    void gameStateHelper_PlayingToDefeat();
    void gameStateHelper_DefeatToPlaying();

    //Playing / Victory
    void gameStateHelper_PlayingToVictory();
    void gameStateHelper_VictoryToPlaying();

    //Playing / GameOver
    void gameStateHelper_PlayingToGameOver();
    void gameStateHelper_GameOverToPlaying();


    // iVars //
private:
    //GameObjects
    GameBackground m_background;
    Bomber         m_bomber;
    Paddle         m_paddle;
    BombManager    m_bombManager;

    //Texts
    Lore::Text       m_pauseText;
    CoreClock::Clock m_pauseBlinkTimer;

    Lore::Text m_scoreText;
    Lore::Text m_turnText;

    //HouseKepping
    int   m_turnNumber;
    int   m_score;
    State m_state;
};

NS_GAMEKABOOM_END
#endif // __Game_Kaboom_include_GameScene_h__ //
