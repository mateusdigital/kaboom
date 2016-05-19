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



////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
Bomb::Bomb()
{
    initSprites();
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
    m_animationTimer.update(dt);
}

void Bomb::draw()
{
    m_pCurrentSprite->draw();
}


////////////////////////////////////////////////////////////////////////////////
// Private Methods                                                            //
////////////////////////////////////////////////////////////////////////////////
void Bomb::initSprites()
{
    //Load the sprites.
    m_aliveSprite.loadTexture("Bomb_Alive.png");
    m_explodedSprite.loadTexture("Bomb_Exploded.png");

    //Setup the Frames Properties.
    setupFrames(m_aliveSprite,    m_aliveFrames,    kSpriteFramesCount_Alive);
    setupFrames(m_explodedSprite, m_explodedFrames, kSpriteFramesCount_Exploded);
    m_frameIndex = 0;

    //Set the pointers.
    m_pCurrentSprite = &m_aliveSprite;
    m_pCurrentFrames = &m_aliveFrames;

    //Setup the Animation Timer
    m_animationTimer.setInterval    (kTimerSpriteFrameChange);
    m_animationTimer.setRepeatCount (CoreClock::Clock::kRepeatForever);
    auto callback = COREGAME_CALLBACK_0(Bomb::onAnimationTimerTick, this);
    m_animationTimer.setTickCallback(callback);

    //
    m_animationTimer.start();
    changeSpriteFrame(0);
    bool flipped = Lore::GameManager::instance()->getRandomNumber(0, 1);
    m_pCurrentSprite->setFlipX(flipped);
}

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

