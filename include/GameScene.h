#ifndef __Game_Kaboom_include_GameScene_h__
#define __Game_Kaboom_include_GameScene_h__

//Lore
#include "Lore.h"
//Game_Kaboom
#include "GameKaboom_Utils.h"
#include "Bomber.h"
#include "Bomb.h"


NS_GAMEKABOOM_BEGIN

class GameScene : public Lore::Scene
{
    // Enums //
private:
    enum class State
    {
        Playing,
        Paused,
        Victory,
        Defeat,
        GameOver
    };


    // Load / Unload //
public:
    virtual void load  () override;
    virtual void unload() override;


    // Update / Draw / Handle Events //
public:
    virtual void update(float dt) override;
    virtual void draw()           override;


    // Private Methods //
private:
    //Inits
    void initBomber();
    void initBombs ();
    void initTexts ();

    //Bomb Helpers
    void resetAllBombs();
    void stopAllBombs ();

    int  getFirstAvaiableBombIndex();
    void createBombHelper();

    void explodeNextBomb();


    //Texts Helpers
    void updateScoreText     ();
    void updateTurnNumberText();


    //Bomber / Bomb Callbacks
    void onBomberBombDropped(const Lore::Vector2 &pos);
    void onBomberAllBombsDropped();

    void onBombExplodeFinished();
    void onBombReachTarget();


    // iVars //
private:
    //GameObjects
    Bomber m_bomber;
    std::vector<std::unique_ptr<Bomb>> m_bombsVec;

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
