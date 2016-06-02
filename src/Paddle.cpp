//Header
#include "Paddle.h"

//Usings
USING_NS_GAMEKABOOM;


////////////////////////////////////////////////////////////////////////////////
// Constants                                                                  //
////////////////////////////////////////////////////////////////////////////////
constexpr int kInitialLivesCount   = 3;
constexpr int kPaddleOffsetY       = 55;
constexpr int kFramesCount         = 4;
constexpr float kAnimationInterval = 0.1;


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
Paddle::Paddle() :
    //HouseKeeping
    m_basePosition(Lore::Vector2::Zero()),
    m_speed       (Lore::Vector2::Zero()),
    m_hitBox      (Lore::Rectangle::Empty()),
    m_lives       (kInitialLivesCount),
    //Movement
    m_maxX(0),
    m_minX(0)
    //m_spritesInfoVec - Initialized in initSprites
{
    initSprites();
}

Paddle::~Paddle()
{
    //Empty...
}


////////////////////////////////////////////////////////////////////////////////
// Update / Draw                                                              //
////////////////////////////////////////////////////////////////////////////////
void Paddle::update(float dt)
{
    handleInput();
    m_basePosition = m_basePosition + (m_speed * dt);

    //Calculate the bounds.
         if(m_basePosition.x < m_minX) m_basePosition.x = m_minX;
    else if(m_basePosition.x > m_maxX) m_basePosition.x = m_maxX;

    for(int i = 0; i < m_lives; ++i)
        m_spritesInfoVec[i].update(dt);
}

void Paddle::draw()
{
    for(int i = 0; i < m_lives; ++i)
        m_spritesInfoVec[i].draw(m_basePosition, kPaddleOffsetY * i);
}


////////////////////////////////////////////////////////////////////////////////
// Setters                                                                    //
////////////////////////////////////////////////////////////////////////////////
void Paddle::setInitialPosition(int x, int y)
{
    m_basePosition.x = x - m_spritesInfoVec[0].frames[0].getWidth() / 2;
    m_basePosition.y = y;
}

void Paddle::setMovementBounds(int min, int max)
{
    m_minX = min;
    m_maxX = max - m_spritesInfoVec[0].frames[0].getWidth();
}


////////////////////////////////////////////////////////////////////////////////
// Getters                                                                    //
////////////////////////////////////////////////////////////////////////////////
const Lore::Vector2& Paddle::getPosition() const
{
    return m_basePosition;
}

int Paddle::getLives() const
{
    return m_lives;
}


////////////////////////////////////////////////////////////////////////////////
// Actions                                                                    //
////////////////////////////////////////////////////////////////////////////////
void Paddle::kill()
{
    --m_lives;
}

bool Paddle::checkCollision(const Lore::Rectangle &rect)
{
    for(int i = 0; i < m_lives; ++i)
    {
        auto paddleRect = m_spritesInfoVec[i].sprite.getBounds();
        if(paddleRect.intersects(rect))
        {
            m_spritesInfoVec[i].start();
            return true;
        }
    }

    return false;
}


////////////////////////////////////////////////////////////////////////////////
// Private Methods                                                            //
////////////////////////////////////////////////////////////////////////////////
//Inits
void Paddle::initSprites()
{
    m_basePosition = Lore::Vector2(100, 200);

    //Init the sprite and frames.
    Lore::Sprite sprite("Paddle.png");
    auto spriteBounds = sprite.getBounds();
    auto frameWidth   = spriteBounds.getWidth() / kFramesCount;
    auto frameHeight  = spriteBounds.getHeight();

    std::vector<Lore::Rectangle> framesVec;
    framesVec.reserve(kFramesCount);

    for(int i = 0; i < kFramesCount; ++i)
    {
        framesVec.push_back(
            Lore::Rectangle(i * frameWidth,
                            0,
                            frameWidth,
                            frameHeight)
        );
    }


    //Init the Animation info.
    m_spritesInfoVec.reserve(kInitialLivesCount);
    for(int i = 0; i < kInitialLivesCount; ++i)
    {
        m_spritesInfoVec.push_back(Paddle::AnimationInfo());
        auto &anim = m_spritesInfoVec[i];

        CoreClock::Clock timer(kAnimationInterval, 4, [&](){
            anim.increaseFrame();
        });

        anim.sprite     = sprite;
        anim.frameIndex = 0;
        anim.frames     = framesVec;
        anim.timer      = timer;

        anim.resetFrame();
    }
}

//Input
void Paddle::handleInput()
{
    auto inputMgr = Lore::InputManager::instance();

    m_speed = Lore::Vector2::Zero();
    if(inputMgr->isKeyDown(SDL_SCANCODE_LEFT))
        m_speed.x += -800;
    if(inputMgr->isKeyDown(SDL_SCANCODE_RIGHT))
        m_speed.x += +800;
}


////////////////////////////////////////////////////////////////////////////////
// Animation Info Methods                                                     //
////////////////////////////////////////////////////////////////////////////////
void Paddle::AnimationInfo::start()
{
    KABOOM_DLOG("Starting paddle hit timer");

    resetFrame();

    timer.stop();
    timer.start();
}

void Paddle::AnimationInfo::update(float dt)
{
    timer.update(dt);
}

void Paddle::AnimationInfo::draw(const Lore::Vector2 &pos, int yOffset)
{
    sprite.setPosition(pos.x, pos.y + yOffset);
    sprite.draw();
}

void Paddle::AnimationInfo::resetFrame()
{
    changeFrame(0);
}

void Paddle::AnimationInfo::increaseFrame()
{
    frameIndex = (frameIndex + 1) % kFramesCount;
    changeFrame(frameIndex);
}

void Paddle::AnimationInfo::changeFrame(int index)
{
    frameIndex = index;
    sprite.setSourceRectangle(frames[frameIndex]);

    KABOOM_DLOG("Chaging Paddle frame to index: %d", frameIndex);
}
