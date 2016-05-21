#ifndef __Game_Kaboom_include_Bomber_h__
#define __Game_Kaboom_include_Bomber_h__

//std
#include <functional>
//Lore
#include "Lore.h"
//Game_Kaboom
#include "GameKaboom_Utils.h"

NS_GAMEKABOOM_BEGIN

class Bomber : public Lore::IDrawable, public Lore::IUpdatable
{
    // Enums / Constants / Typdefs //
public:
    typedef std::function<void (const Lore::Vector2 &bombPos)> BombDroppedCallback;
    typedef std::function<void ()> AllBombsDroppedCallback;

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
    void startDropBombs(int turnNumber);
    void stopDropBombs ();

    void makeWinTurn ();
    void makeLoseTurn();


    // Setters //
public:
    //Position / Movement
    void setInitialPosition(const Lore::Vector2 &pos);

    void setMovementBounds(const Lore::Vector2 &min,
                           const Lore::Vector2 &max);

    //Callbacks
    void setOnBombDroppedCallback(const BombDroppedCallback &callback);
    void setOnAllBombsDroppedCallback(const AllBombsDroppedCallback &callback);


    // Getters //
public:
    int getTurnNumber() const;

    int getTurnBombsCount         () const;
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
    Lore::Vector2 m_minBounds;
    Lore::Vector2 m_maxBounds;

    //Turn / Bombs
    int m_turnNumber;

    int m_turnBombs;
    int m_bombsDropped;
    int m_bombsRemaining;

    bool m_isDroppingBombs;

    //Callbacks
    BombDroppedCallback     m_bombDroppedCallback;
    AllBombsDroppedCallback m_allBombsDroppedCallback;

    //Other
    CoreRandom::Random m_random;

    MoveState m_moveState;
    float     m_dropSpot;
};

NS_GAMEKABOOM_END
#endif // __Game_Kaboom_include_Bomber_h__ //
