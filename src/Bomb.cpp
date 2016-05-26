//Header
#include "Bomb.h"

//Usings
USING_NS_GAMEKABOOM;


////////////////////////////////////////////////////////////////////////////////
// Constants                                                                  //
////////////////////////////////////////////////////////////////////////////////
constexpr int kSpriteFramesCount_Alive    = 4;
constexpr int kSpriteFramesCount_Exploded = 3;

constexpr float kTimerSpriteFrameChange = 0.3f;
constexpr float kTimerBombExplode       = 0.3f;


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
Bomb::Bomb() :
    //HouseKeeping
    m_state(Bomb::State::Dead),
    //Sprite / Animation
    //m_aliveSprite    - Initialized in initSprites()
    //m_explodedSprite - Initialized in initSprites()
    m_pCurrentSprite(nullptr),
    //m_aliveFrames    - Initialized in initSprites()
    //m_explodedFrames - Initialized in initSprites()
    m_pCurrentFrames(nullptr),
    m_frameIndex    (0),
    //m_animationTimer - Initialized in initTimers()
    //Movement / Bounds
    m_pos            (Lore::Vector2::Zero()),
    m_speed          (Lore::Vector2::Zero()),
    m_initialPosition(Lore::Vector2::Zero())
    //Exploded
    //m_explodeTimer - Initialized in initTimers()
    //Callback
    //m_reachTargetCallback      - Default initialized
    //m_explodedFinishedCallback - Default initialized
{
    initSprites();
    initTimers ();
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

    m_animationTimer.update(dt);
    m_explodeTimer.update  (dt);

    if(m_state == Bomb::State::Alive)
    {
        setPosition(getPosition() + (m_speed * dt));

        if(getPosition().y >= m_maxBounds.y)
            m_reachTargetCallback();
    }
}

void Bomb::draw()
{
    if(m_state == Bomb::State::Dead)
        return;

    m_pCurrentSprite->setPosition(m_pos);
    m_pCurrentSprite->draw();
}


////////////////////////////////////////////////////////////////////////////////
// Actions                                                                    //
////////////////////////////////////////////////////////////////////////////////
void Bomb::reset()
{
    m_state = Bomb::State::Dead;

    m_explodeTimer.stop();
}

void Bomb::explode()
{
    m_state = Bomb::State::Exploding;

    m_pCurrentSprite = &m_explodedSprite;
    m_pCurrentFrames = &m_explodedFrames;
    changeSpriteFrame(0);

    m_explodeTimer.start();
}

void Bomb::startDropping(int turnNumber)
{
    m_state = Bomb::State::Alive;

    m_pCurrentSprite = &m_aliveSprite;
    m_pCurrentFrames = &m_aliveFrames;
    changeSpriteFrame(0);

    m_explodeTimer.stop();

    //COWTODO: Decide the speed;
    m_speed = Lore::Vector2(0, 200);
}

void Bomb::stopDropping()
{
    m_speed = Lore::Vector2::Zero();
}

////////////////////////////////////////////////////////////////////////////////
// Setters                                                                    //
////////////////////////////////////////////////////////////////////////////////
void Bomb::setPosition(const Lore::Vector2 &pos)
{
    m_pos = pos;
}

void Bomb::setMovementBounds(const Lore::Vector2 &bounds)
{
    m_maxBounds = bounds;
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

Bomb::State Bomb::getState() const
{
    return m_state;
}



////////////////////////////////////////////////////////////////////////////////
// Private Methods                                                            //
////////////////////////////////////////////////////////////////////////////////
//Inits
void Bomb::initSprites()
{
    //Load the sprites.
    m_aliveSprite.loadTexture   ("Bomb_Alive.png");
    m_explodedSprite.loadTexture("Bomb_Exploded.png");

    //Setup the Frames Properties.
    setupFrames(m_aliveSprite,    m_aliveFrames,    kSpriteFramesCount_Alive);
    setupFrames(m_explodedSprite, m_explodedFrames, kSpriteFramesCount_Exploded);
    m_frameIndex = 0;

    //Set the pointers.
    m_pCurrentSprite = &m_aliveSprite;
    m_pCurrentFrames = &m_aliveFrames;

    changeSpriteFrame(0);

    bool flipped = Lore::GameManager::instance()->getRandomNumber(0, 1);
    m_pCurrentSprite->setFlipX(flipped);
}

void Bomb::initTimers()
{
    //Setup the Animation Timer
    m_animationTimer.setInterval(kTimerSpriteFrameChange);
    m_animationTimer.setRepeatCount(CoreClock::Clock::kRepeatForever);

    auto animCallback = COREGAME_CALLBACK_0(Bomb::onAnimationTimerTick, this);
    m_animationTimer.setTickCallback(animCallback);

    m_animationTimer.start();

    //Setup the Explode Timer.
    m_explodeTimer.setInterval(kTimerBombExplode);
    m_explodeTimer.setRepeatCount(1);

    auto explodeCallback = COREGAME_CALLBACK_0(Bomb::onExplodeTimerTick, this);
    m_explodeTimer.setTickCallback(explodeCallback);
}


//Helpers
void Bomb::setupFrames(const Lore::Sprite &sprite,
                       std::vector<Lore::Rectangle> &framesVec,
                       int framesCount)
{
    //Get the Frame Properties.
    auto rect   = sprite.getSourceRectangle();
    auto frameW = rect.getWidth () / framesCount;
    auto frameH = rect.getHeight();

    //Create the Frames Rectangles.
    framesVec.reserve(framesCount);

    for(int i = 0; i < framesCount; ++i)
    {
        Lore::Rectangle frameRect(i * frameW, 0, frameW, frameH);
        framesVec.push_back(frameRect);
    }
}

void Bomb::changeSpriteFrame(int frameIndex)
{
    m_frameIndex = frameIndex;
    m_pCurrentSprite->setSourceRectangle((*m_pCurrentFrames)[m_frameIndex]);
}


//Timer Callback
void Bomb::onAnimationTimerTick()
{
    auto frameIndex = (++m_frameIndex % m_pCurrentFrames->size());
    changeSpriteFrame(frameIndex);
}

void Bomb::onExplodeTimerTick()
{
    m_state = State::Dead;
    m_explodedFinishedCallback();
}
