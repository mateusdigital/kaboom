//Header
#include "Bomber.h"

//Usings
USING_NS_GAMEKABOOM;


////////////////////////////////////////////////////////////////////////////////
// Constants                                                                  //
////////////////////////////////////////////////////////////////////////////////
constexpr int kSpriteFrames = 3;

constexpr int kFrameIndex_Happy    = 1;
constexpr int kFrameIndex_Sad      = 0;
constexpr int kFrameIndex_BigMouth = 2;

constexpr int kBodyOffsetY =  10;
constexpr int kBombOffsetX =   5;
constexpr int kBombOffsetY = -45;

constexpr int kMoveMinDisplacement = 50;


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
Bomber::Bomber() :
    //Sprite / Animation
    //m_sprite       - Default initialized.
    //m_spriteFrames - Default initialized.
    m_frameIndex(kFrameIndex_Sad),
    //Movement / Bounds
    m_speed          (Lore::Vector2::Zero()),
    m_initialPosition(Lore::Vector2::Zero()),
    m_minBounds      (0),
    m_maxBounds      (0),
    //Turn / Bombs
    //m_turnInfo - Initialized in reset.
    m_bombsDropped   (0),
    m_bombsRemaining (0),
    m_isDroppingBombs(0),
    //Callbacks
    // m_bombDroppedCallback - Default initialized.
    //Other
    m_random(CoreRandom::Random::kRandomSeed)
{
    initSprites();
}

Bomber::~Bomber()
{
    //Empty...
}


////////////////////////////////////////////////////////////////////////////////
// Update / Draw                                                              //
////////////////////////////////////////////////////////////////////////////////
void Bomber::update(float dt)
{
    //Did drop all bombs already...
    if(!m_isDroppingBombs)
        return;

    auto x = m_sprite.getPosition().x;

    //Reach the drop spot - Drop a bomb.
    if((x <= m_dropSpot && m_speed.x < 0) ||
       (x >= m_dropSpot && m_speed.x > 0))
    {
        dropBomb();
        deciceNextDropSpot();
    }

    //Not at drop stop - Move towards it.
    else
    {
        m_sprite.move(m_speed * dt);
    }
}

void Bomber::draw()
{
    m_sprite.draw();
}


////////////////////////////////////////////////////////////////////////////////
// Actions                                                                    //
////////////////////////////////////////////////////////////////////////////////
void Bomber::reset(const TurnInfo &turnInfo)
{
    m_isDroppingBombs = false;
    m_turnInfo        = turnInfo;
    m_bombsRemaining  = m_turnInfo.bombsCount;
    m_bombsDropped    = 0;
}

void Bomber::startDropBombs()
{
    m_isDroppingBombs = true;

    changeSpriteFrame(kFrameIndex_BigMouth);
    deciceNextDropSpot();
}

void Bomber::stopDropBombs()
{
    m_isDroppingBombs = false;
}

void Bomber::makeWinTurn()
{
    changeSpriteFrame(kFrameIndex_Happy);
}

void Bomber::makeLoseTurn()
{
    changeSpriteFrame(kFrameIndex_Sad);
}



////////////////////////////////////////////////////////////////////////////////
// Setters                                                                    //
////////////////////////////////////////////////////////////////////////////////
//Position / Movement
void Bomber::setInitialPosition(int x, int y)
{
    m_initialPosition.x = x - m_sprite.getBounds().getWidth() / 2;
    m_initialPosition.y = y + kBodyOffsetY;

    m_sprite.setOrigin(Lore::ITransformable::OriginHelpers::BottomLeft());
    m_sprite.setPosition(m_initialPosition);
}

void Bomber::setMovementBounds(int min, int max)
{
    m_minBounds = min;
    m_maxBounds = max - m_sprite.getBounds().getWidth();
}


//Callbacks
void Bomber::setOnBombDroppedCallback(const BombDroppedCallback &callback)
{
    m_bombDroppedCallback = callback;
}


////////////////////////////////////////////////////////////////////////////////
// Getters                                                                    //
////////////////////////////////////////////////////////////////////////////////
int Bomber::getTurnBombsDroppedCount() const
{
    return m_bombsDropped;
}

int Bomber::getTurnBombsRemainingCount() const
{
    return m_bombsRemaining;
}


bool Bomber::isDroppingBombs() const
{
    return m_isDroppingBombs;
}


////////////////////////////////////////////////////////////////////////////////
// Private Methods                                                            //
////////////////////////////////////////////////////////////////////////////////
void Bomber::initSprites()
{
    m_sprite.loadTexture("Bomber.png");

    //Get the Frame Properties.
    auto rect   = m_sprite.getSourceRectangle();
    auto frameW = rect.getWidth () / kSpriteFrames;
    auto frameH = rect.getHeight();

    //Create the Frames Rectangles.
    m_spriteFrames.reserve(kSpriteFrames);

    for(int i = 0; i < kSpriteFrames; ++i)
    {
        m_spriteFrames.push_back(
            Lore::Rectangle(i * frameW, 0, frameW, frameH)
        );
    }

    //Set the initial frame.
    changeSpriteFrame(kFrameIndex_Happy);
}

void Bomber::changeSpriteFrame(int frameIndex)
{
    m_frameIndex = frameIndex;
    m_sprite.setSourceRectangle(m_spriteFrames[m_frameIndex]);
}

void Bomber::deciceNextDropSpot()
{
    m_dropSpot = m_random.next(m_minBounds, m_maxBounds);

    if(m_dropSpot < m_sprite.getPosition().x)
    {
        m_dropSpot -= kMoveMinDisplacement;
        m_speed.x = -m_turnInfo.bomberSpeed;
    }
    else
    {
        m_dropSpot += kMoveMinDisplacement;
        m_speed.x = +m_turnInfo.bomberSpeed;
    }

    m_dropSpot = static_cast<int>(Lore::MathHelper::clamp(m_dropSpot,
                                                          m_minBounds,
                                                          m_maxBounds));
}

void Bomber::dropBomb()
{
    //Dropped all bombs?
    if(m_bombsRemaining == 0)
    {
        KABOOM_DLOG("Bomber::dropBomb - All bombs has been dropped");

        m_isDroppingBombs = false;
        changeSpriteFrame(kFrameIndex_Happy);

        return;
    }

    //Update the bombs stats.
    --m_bombsRemaining;
    ++m_bombsDropped;

    //Adjust the bomb to be placed where the bomber is.
    auto bombPosition = m_sprite.getPosition();
    bombPosition.x += kBombOffsetX;
    bombPosition.y += kBombOffsetY;
    m_bombDroppedCallback(bombPosition);

    KABOOM_DLOG("Bomb dropped - Dropped %d - Remaining %d",
                m_bombsDropped,
                m_bombsRemaining);
}
