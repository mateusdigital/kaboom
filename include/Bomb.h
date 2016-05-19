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


    // CTOR / DTOR //
public:
    Bomb();
    virtual ~Bomb();


    // Update / Draw //
public:
    virtual void update(float dt) override;
    virtual void draw()           override;


    // Setters //
public:
    void setPosition(const Lore::Vector2 &pos)
    {
        m_pCurrentSprite->setPosition(pos);
    }

    // Private Methods //
private:
    void initSprites();
    void setupFrames(const Lore::Sprite &sprite,
                     std::vector<Lore::Rectangle> &framesVec,
                     int framesCount);

    void changeSpriteFrame(int frameIndex);


    //Timer Callbacks
    void onAnimationTimerTick();

    // iVars //
private:
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
    Lore::Vector2 m_speed;
    Lore::Vector2 m_initialPosition;
};

NS_GAMEKABOOM_END
#endif // __Game_Kaboom_include_Bomb_h__ //
