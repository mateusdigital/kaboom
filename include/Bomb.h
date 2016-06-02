#ifndef __Game_Kaboom_include_Bomb_h__
#define __Game_Kaboom_include_Bomb_h__

//std
#include <functional>
//Game_Kaboom
#include "GameKaboom_Utils.h"
#include "TurnInfo.h"


NS_GAMEKABOOM_BEGIN

class Bomb : public Lore::IDrawable, public Lore::IUpdatable
{
    // Inner Types //
private:
    struct AnimationInfo
    {
        std::string name;
        Lore::Sprite                  sprite;
        std::vector<Lore::Rectangle>  framesVec;
        int                           frameIndex;
        CoreClock::Clock              timer;

        // Animation Management //
        void start();
        void stop ();

        // Frame Management //
        void incrementFrame();
        void changeFrame(int index);

        // Update / Draw //
        void update(float dt);
        void draw  (const Lore::Vector2 &pos);

        // Setup //
        void setupFrames(const std::string &spriteName,
                         int framesCount);

        void setupTimer(float interval,
                        int repeatCount,
                        const CoreClock::Clock::Callback &tickCallback,
                        const CoreClock::Clock::Callback &doneCallback);
    };


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
    void reset(const TurnInfo &turnInfo);
    void explode();

    void startDropping();
    void stopDropping ();

    void kill();


    // Setters //
public:
    void setPosition(const Lore::Vector2 &pos);
    void setMovementBounds(int maxY);

    void setOnReachTargetCallback    (const ReachTargetCallback     &callback);
    void setOnExplodeFinishedCallback(const ExplodeFinishedCallback &callback);


    // Getters //
public:
    const Lore::Vector2& getPosition() const;
    const Lore::Rectangle& getHitBox() const;

    State getState() const;


    // Private Methods //
private:
    //Init
    void initAnimations();
    void initTimers    ();

    //Timer Callbacks
    void onAliveAnimationTimerTick    ();
    void onExplodingAnimationTimerTick();
    void onExplodingAnimationFinished ();


    // iVars //
private:
    //HouseKeeping
    TurnInfo        m_turnInfo;
    State           m_state;
    Lore::Rectangle m_hitBox;

    //Sprite / Animation
    AnimationInfo  m_aliveAnimation;
    AnimationInfo  m_explodingAnimation;
    AnimationInfo *m_pCurrentAnimation;

    //Movement / Bounds
    Lore::Vector2 m_pos;
    Lore::Vector2 m_speed;
    int           m_maxY;

    //Callbacks
    ReachTargetCallback     m_reachTargetCallback;
    ExplodeFinishedCallback m_explodedFinishedCallback;
};

NS_GAMEKABOOM_END
#endif // __Game_Kaboom_include_Bomb_h__ //
