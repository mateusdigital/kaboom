#ifndef __Game_Kaboom_include_Bomb_h__
#define __Game_Kaboom_include_Bomb_h__

//std
#include <functional>
//Lore
#include "Lore.h"
//Game_Kaboom
#include "GameKaboom_Utils.h"

NS_GAMEKABOOM_BEGIN

class Bomb : public Lore::IDrawable, public Lore::IUpdatable
{
    // Enums / Constants / Typdefs //
public:
    enum class State
    {
        Alive,
        Exploding,
        Dead
    };

    typedef std::function<void ()> ExplodeFinishedCallback;
    typedef std::function<void ()> ReachTargetCallback;


    // CTOR / DTOR //
public:
    Bomb();
    virtual ~Bomb();


    // Update / Draw //
public:
    virtual void update(float dt) override;
    virtual void draw()           override;


    // Actions //
public:
    void reset  ();
    void explode();

    void startDropping(int turnNumber);
    void stopDropping ();


    // Setters //
public:
    void setPosition(const Lore::Vector2 &pos);
    void setMovementBounds(const Lore::Vector2 &bounds);

    void setOnReachTargetCallback    (const ReachTargetCallback     &callback);
    void setOnExplodeFinishedCallback(const ExplodeFinishedCallback &callback);


    // Getters //
public:
    const Lore::Vector2& getPosition() const;
    State getState() const;


    // Private Methods //
private:
    //Init
    void initSprites();
    void initTimers ();

    //Helpers
    void setupFrames(const Lore::Sprite &sprite,
                     std::vector<Lore::Rectangle> &framesVec,
                     int framesCount);

    void changeSpriteFrame(int frameIndex);

    //Timer Callbacks
    void onAnimationTimerTick();
    void onExplodeTimerTick  ();


    // iVars //
private:
    //HouseKeeping
    State m_state;

    //Sprite / Animation
    Lore::Sprite  m_aliveSprite;
    Lore::Sprite  m_explodedSprite;
    Lore::Sprite *m_pCurrentSprite;

    std::vector<Lore::Rectangle>  m_aliveFrames;
    std::vector<Lore::Rectangle>  m_explodedFrames;
    std::vector<Lore::Rectangle> *m_pCurrentFrames;

    int m_frameIndex;
    CoreClock::Clock m_animationTimer;

    //Movement / Bounds
    Lore::Vector2 m_pos;
    Lore::Vector2 m_speed;
    Lore::Vector2 m_initialPosition;
    Lore::Vector2 m_maxBounds;

    //Exploded
    CoreClock::Clock m_explodeTimer;

    //Callback
    ReachTargetCallback     m_reachTargetCallback;
    ExplodeFinishedCallback m_explodedFinishedCallback;
};

NS_GAMEKABOOM_END
#endif // __Game_Kaboom_include_Bomb_h__ //
