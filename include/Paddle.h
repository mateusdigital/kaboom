#ifndef __Game_Kaboom_include_Paddle_h__
#define __Game_Kaboom_include_Paddle_h__

//Game_Kaboom
#include "GameKaboom_Utils.h"

NS_GAMEKABOOM_BEGIN

class Paddle : public Lore::IDrawable, public Lore::IUpdatable
{
    // Inner Types //
private:
    struct AnimationInfo
    {
        Lore::Sprite                 sprite;
        std::vector<Lore::Rectangle> frames;
        int                          frameIndex;
        CoreClock::Clock             timer;

        void start();

        void update(float dt);
        void draw(const Lore::Vector2 &pos, int yOffset);

        void resetFrame();
        void increaseFrame();
        void changeFrame(int index);
    };

    // Enums / Constants / Typdefs //
public:

    // CTOR / DTOR //
public:
    Paddle();
    virtual ~Paddle();


    // Update / Draw //
public:
    virtual void update(float dt) override;
    virtual void draw()           override;


    // Setters //
public:
    void setInitialPosition(int x, int y);
    void setMovementBounds (int min, int max);


    // Getters //
public:
    const Lore::Vector2& getPosition() const;
    int getLives() const;


    // Actions //
public:
    void kill();
    bool checkCollision(const Lore::Rectangle &rect);


    // Private Methods //
private:
    //Init
    void initSprites();

    //Input
    void handleInput();


    // iVars //
private:
    //HouseKeeping
    Lore::Vector2   m_basePosition;
    Lore::Vector2   m_speed;
    Lore::Rectangle m_hitBox;

    int m_lives;

    //Movement
    int m_maxX;
    int m_minX;

    //Sprite
    std::vector<AnimationInfo> m_spritesInfoVec;
};

NS_GAMEKABOOM_END
#endif // __Game_Kaboom_include_Paddle_h__ //
