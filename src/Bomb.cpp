//Header
#include "Bomb.h"

//Usings
USING_NS_GAMEKABOOM;


////////////////////////////////////////////////////////////////////////////////
// Constants                                                                  //
////////////////////////////////////////////////////////////////////////////////
constexpr int kSpriteFramesCount_Alive    = 4;
constexpr int kSpriteFramesCount_Exploded = 3;

constexpr float kTimerSpriteFrameChange_Alive     = 0.10f;
constexpr float kTimerSpriteFrameChange_Exploding = 0.07f;
constexpr int   kRepeatCount_Exploding = 5;


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
Bomb::Bomb() :
    //HouseKeeping
    //m_turnInfo - Set in reset.
    m_state(Bomb::State::Dead),
    m_hitBox(Lore::Rectangle::Empty()),
    //Sprite / Animation
    //m_aliveAnimation     - Initialized in InitAnimations
    //m_explodingAnimation - Initialized in InitAnimations
    m_pCurrentAnimation(nullptr),
    //Movement / Bounds
    m_pos            (Lore::Vector2::Zero()),
    m_speed          (Lore::Vector2::Zero()),
    m_maxY           (0)
    //Callback
    //m_reachTargetCallback      - Default initialized
    //m_explodingFinishedCallback - Default initialized
{
    initAnimations();
    initTimers    ();
}

Bomb::~Bomb()
{
    //Empty...
}


////////////////////////////////////////////////////////////////////////////////
// Update / Draw                                                              //
////////////////////////////////////////////////////////////////////////////////
void Bomb::update(float dt)
{
    if(m_state == Bomb::State::Dead)
        return;

    //Update timers.
    m_aliveAnimation.update    (dt);
    m_explodingAnimation.update(dt);

    //Just move if it is alive.
    if(m_state == Bomb::State::Alive)
    {
        setPosition(getPosition() + (m_speed * dt));

        if(getPosition().y >= m_maxY)
            m_reachTargetCallback();
    }
}

void Bomb::draw()
{
    if(m_state == Bomb::State::Dead)
        return;

    m_pCurrentAnimation->draw(m_pos);
}


////////////////////////////////////////////////////////////////////////////////
// Actions                                                                    //
////////////////////////////////////////////////////////////////////////////////
void Bomb::reset(const TurnInfo &turnInfo)
{
    m_turnInfo = turnInfo;

    m_state   = Bomb::State::Dead;
    m_speed.y = m_turnInfo.bombSpeed;
}

void Bomb::explode()
{
    m_state = Bomb::State::Exploding;

    m_pCurrentAnimation->stop();
    m_pCurrentAnimation = &m_explodingAnimation;
    m_pCurrentAnimation->start();
}

void Bomb::startDropping()
{
    m_state = Bomb::State::Alive;

    m_pCurrentAnimation->stop();
    m_pCurrentAnimation = &m_aliveAnimation;
    m_pCurrentAnimation->start();

    auto flipped = Lore::GameManager::instance()->getRandomBool();
    m_pCurrentAnimation->sprite.setFlipX(flipped);
}

void Bomb::stopDropping()
{
    m_speed = Lore::Vector2::Zero();
}

void Bomb::kill()
{
    KABOOM_DLOG("Killing bomb.");
    m_state = Bomb::State::Dead;
}


////////////////////////////////////////////////////////////////////////////////
// Setters                                                                    //
////////////////////////////////////////////////////////////////////////////////
void Bomb::setPosition(const Lore::Vector2 &pos)
{
    m_pos = pos;
    m_hitBox.setLocation(m_pos);
}

void Bomb::setMovementBounds(int maxY)
{
    m_maxY = maxY;
}

void Bomb::setOnReachTargetCallback(const ReachTargetCallback &callback)
{
    m_reachTargetCallback = callback;
}

void Bomb::setOnExplodeFinishedCallback(const ExplodeFinishedCallback &callback)
{
    m_explodedFinishedCallback = callback;
}



////////////////////////////////////////////////////////////////////////////////
// Getters                                                                    //
////////////////////////////////////////////////////////////////////////////////
const Lore::Vector2& Bomb::getPosition() const
{
    return m_pos;
}

const Lore::Rectangle& Bomb::getHitBox() const
{
    return m_hitBox;
}

Bomb::State Bomb::getState() const
{
    return m_state;
}



////////////////////////////////////////////////////////////////////////////////
// Private Methods                                                            //
////////////////////////////////////////////////////////////////////////////////
//Inits
void Bomb::initAnimations()
{
    //Setup the Frames.
    m_aliveAnimation.name = "Alive";
    m_aliveAnimation.setupFrames("Bomb_Alive.png",
                                  kSpriteFramesCount_Alive);
    m_aliveAnimation.changeFrame(0);

    m_explodingAnimation.name = "Exploding";
    m_explodingAnimation.setupFrames("Bomb_Exploded.png",
                                     kSpriteFramesCount_Exploded);
    m_explodingAnimation.changeFrame(0);

    //Set the pointers.
    m_pCurrentAnimation = &m_aliveAnimation;

    //Set the hit box.
    m_hitBox.setSize(m_pCurrentAnimation->framesVec[0].getSize());
}

void Bomb::initTimers()
{
    //Setup the Alive Timer
    m_aliveAnimation.setupTimer(
            kTimerSpriteFrameChange_Alive,
            CoreClock::Clock::kRepeatForever,
            COREGAME_CALLBACK_0(Bomb::onAliveAnimationTimerTick, this),
            [](){} //Empty callback.
    );

    //Setup the Exploding Timer
    m_explodingAnimation.setupTimer(
            kTimerSpriteFrameChange_Exploding,
            kRepeatCount_Exploding,
            COREGAME_CALLBACK_0(Bomb::onExplodingAnimationTimerTick, this),
            COREGAME_CALLBACK_0(Bomb::onExplodingAnimationFinished,  this)
    );
}


//Timer Callback
void Bomb::onAliveAnimationTimerTick()
{
    m_pCurrentAnimation->incrementFrame();
}

void Bomb::onExplodingAnimationTimerTick()
{
    auto gameMgr     = Lore::GameManager::instance();
    auto framesCount = m_pCurrentAnimation->framesVec.size() -1;

    auto r = gameMgr->getRandomNumber(0, 255);
    auto g = gameMgr->getRandomNumber(0, 255);
    auto b = gameMgr->getRandomNumber(0, 255);

    auto frameIndex = gameMgr->getRandomNumber(0, framesCount);

    m_pCurrentAnimation->sprite.setColor(Lore::Color(r, g, b));
    m_pCurrentAnimation->changeFrame(frameIndex);
}

void Bomb::onExplodingAnimationFinished()
{
    m_state = Bomb::State::Dead;
    m_explodedFinishedCallback();
}



////////////////////////////////////////////////////////////////////////////////
// Bomb Animation Info                                                        //
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Animation Management                                                       //
////////////////////////////////////////////////////////////////////////////////
void Bomb::AnimationInfo::start()
{
    timer.start();
    frameIndex = Lore::GameManager::instance()->getRandomNumber(0, framesVec.size());
    changeFrame(frameIndex);
}

void Bomb::AnimationInfo::stop()
{
    timer.stop();
}


////////////////////////////////////////////////////////////////////////////////
// Frame Management                                                           //
////////////////////////////////////////////////////////////////////////////////
void Bomb::AnimationInfo::incrementFrame()
{
    frameIndex = (frameIndex + 1) % framesVec.size();
    changeFrame(frameIndex);
}

void Bomb::AnimationInfo::changeFrame(int index)
{
    sprite.setSourceRectangle(framesVec[index]);
}


////////////////////////////////////////////////////////////////////////////////
// Update / Draw                                                              //
////////////////////////////////////////////////////////////////////////////////
void Bomb::AnimationInfo::update(float dt)
{
    timer.update(dt);
}

void Bomb::AnimationInfo::draw(const Lore::Vector2 &pos)
{
    sprite.setPosition(pos);
    sprite.draw();
}


////////////////////////////////////////////////////////////////////////////////
// Setup                                                                      //
////////////////////////////////////////////////////////////////////////////////
void Bomb::AnimationInfo::setupFrames(const std::string &spriteName,
                                      int framesCount)
{
    //Load the texture.
    sprite.loadTexture(spriteName);

    //Get the Frame Properties.
    auto rect   = sprite.getSourceRectangle();
    auto frameW = rect.getWidth () / framesCount;
    auto frameH = rect.getHeight();

    //Create the Frames Rectangles.
    framesVec.reserve(framesCount);

    for(int i = 0; i < framesCount; ++i)
    {
        framesVec.push_back(
            Lore::Rectangle(i * frameW, 0,
                            frameW, frameH)
        );
    }

    frameIndex = 0;
    changeFrame(frameIndex);
}

void Bomb::AnimationInfo::setupTimer(float interval,
                                     int repeatCount,
                                     const CoreClock::Clock::Callback &tickCallback,
                                     const CoreClock::Clock::Callback &doneCallback)
{
    timer.setInterval    (interval);
    timer.setRepeatCount (repeatCount);
    timer.setTickCallback(tickCallback);
    timer.setDoneCallback(doneCallback);
}
