#ifndef __Game_Kaboom_include_Bomber_h__
#define __Game_Kaboom_include_Bomber_h__

//std
#include <functional>
//Game_Kaboom
#include "GameKaboom_Utils.h"
#include "TurnInfo.h"


NS_GAMEKABOOM_BEGIN

class Bomber : public Lore::IDrawable, public Lore::IUpdatable
{
    // Enums / Constants / Typdefs //
public:
    typedef std::function<void (const Lore::Vector2 &bombPos)> BombDroppedCallback;

private:
    enum class MoveState { MovingToTarget, DroppingBomb };


    // CTOR / DTOR //
public:
    Bomber();
    virtual ~Bomber();


    // Update / Draw //
public:
    virtual void update(float dt) override;
    virtual void draw()           override;


    // Actions //
public:
    void reset(const TurnInfo &turnInfo);

    void startDropBombs();
    void stopDropBombs ();

    void makeWinTurn ();
    void makeLoseTurn();


    // Setters //
public:
    //Position / Movement
    void setInitialPosition(int x, int y);
    void setMovementBounds(int min, int max);

    //Callbacks
    void setOnBombDroppedCallback(const BombDroppedCallback &callback);


    // Getters //
public:
    int getTurnBombsDroppedCount  () const;
    int getTurnBombsRemainingCount() const;

    bool isDroppingBombs() const;


    // Private Methods //
private:
    void initSprites();

    void changeSpriteFrame(int frameIndex);

    void deciceNextDropSpot();
    void dropBomb();

    // iVars //
private:
    //Sprite / Animation
    Lore::Sprite                 m_sprite;
    std::vector<Lore::Rectangle> m_spriteFrames;
    int                          m_frameIndex;

    //Movement / Bounds
    Lore::Vector2 m_speed;
    Lore::Vector2 m_initialPosition;
    int           m_minBounds;
    int           m_maxBounds;

    //Turn / Bombs
    TurnInfo m_turnInfo;
    int      m_bombsDropped;
    int      m_bombsRemaining;

    bool m_isDroppingBombs;

    //Callbacks
    BombDroppedCallback m_bombDroppedCallback;

    MoveState m_moveState;
    float     m_dropSpot;
};

NS_GAMEKABOOM_END
#endif // __Game_Kaboom_include_Bomber_h__ //
