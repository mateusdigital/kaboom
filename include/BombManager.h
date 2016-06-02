#ifndef __Game_Kaboom_include_BombManager_h__
#define __Game_Kaboom_include_BombManager_h__

//Lore
#include "Lore.h"
//Game_Kaboom
#include "GameKaboom_Utils.h"
#include "Bomb.h"
#include "Paddle.h"
#include "TurnInfo.h"


NS_GAMEKABOOM_BEGIN

class BombManager
{
    // Typedefs //
public:
    typedef std::function<void ()> BombCaughtCallback;
    typedef std::function<void ()> AllBombsCaughtCallback;

    typedef std::function<void ()> BombReachTargetCallback;

    typedef std::function<void ()> BombExplodeCallback;
    typedef std::function<void ()> AllBombsExplodedCallback;


    // CTOR / DTOR //
public:
    BombManager();
    ~BombManager();


    // Update / Draw //
public:
    void update(float dt);
    void draw();


    // Actions //
public:
    void reset(const TurnInfo &turnInfo);
    void dropBombAt(const Lore::Vector2 &pos);
    void checkCollision(Paddle &paddle);


    // Setters //
public:
    //Movement
    void setBombMovementBounds(int maxY);

    //Callbacks
    void setOnBombCaughtCallback    (const BombCaughtCallback     &callback);
    void setOnAllBombsCaughtCallback(const AllBombsCaughtCallback &callback);

    void setOnBombReachTargetCallback(const BombReachTargetCallback &callback);

    void setOnBombExplodeCallback     (const BombExplodeCallback      &callback);
    void setOnAllBombsExplodedCallback(const AllBombsExplodedCallback &callback);



    // Private Methods //
private:
    void sortBombs();
    void createBombHelper();
    void explodeNextBomb();

    void stopAllBombs();
    void resetAllBombs();

    // Sounds Methods //
private:
    void initSounds();

    void playDroppingEffect();
    void stopDroppingEffect();

    void playCaughtEffect();

    // Bombs Callbacks //
private:
    void onBombReachTarget();
    void onBombExplodeFinished();


    // iVars //
private:
    //Bombs
    std::vector<std::unique_ptr<Bomb>> m_bombsVec;

    //HouseKeep
    TurnInfo m_turnInfo;
    int      m_bombsCaught;
    int      m_aliveBombs;
    int      m_maxBombY;
    bool     m_isPlayingDroppingEffect;

    //Callbacks
    BombCaughtCallback       m_onBombCaughtCallback;
    AllBombsCaughtCallback   m_onAllBombsCaughtCallback;

    BombReachTargetCallback  m_onBombReachTargetCallback;

    BombExplodeCallback      m_onBombExplodeCallback;
    AllBombsExplodedCallback m_onAllBombsExplodedCallback;
};

NS_GAMEKABOOM_END
#endif // __Game_Kaboom_include_BombManager_h__ //
