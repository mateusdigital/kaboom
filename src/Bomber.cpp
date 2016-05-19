//Header
#include "Bomber.h"

//Usings
USING_NS_GAMEKABOOM;


////////////////////////////////////////////////////////////////////////////////
// Constants                                                                  //
////////////////////////////////////////////////////////////////////////////////
constexpr int kFrameIndex_Happy    = 1;
constexpr int kFrameIndex_Sad      = 0;
constexpr int kFrameIndex_BigMouth = 2;


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
    m_minBounds      (Lore::Vector2::Zero()),
    m_maxBounds      (Lore::Vector2::Zero()),
    //Turn / Bombs
    m_turnNumber     (0),
    m_turnBombs      (0),
    m_bombsDropped   (0),
    m_bombsRemaining (0),
    m_isDroppingBombs(0),
    //Callbacks
    // m_bombDroppedCallback     - Default initialized.
    // m_allBombsDroppedCallback - Default initialized.
    //Other
    m_random(0)
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
    if(x <= m_dropSpot && m_speed.x < 0 ||
       x >= m_dropSpot && m_speed.x > 0)
    {
        dropBomb();
        deciceNextDropSpot();
    }

    //Not at drop stop - Move towards it
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
void Bomber::startDropBombs()
{
    m_isDroppingBombs = true;
    m_turnBombs       = m_turnNumber + 1;
    m_bombsRemaining  = m_turnBombs;
    m_bombsDropped    = 0;

    changeSpriteFrame(kFrameIndex_BigMouth);
    deciceNextDropSpot();
}


void Bomber::makeWinTurn()
{

}

void Bomber::makeLoseTurn()
{

}



////////////////////////////////////////////////////////////////////////////////
// Setters                                                                    //
////////////////////////////////////////////////////////////////////////////////
//Position / Movement
void Bomber::setInitialPosition(const Lore::Vector2 &pos)
{
    m_initialPosition = pos;
    m_sprite.setPosition(pos);
}

void Bomber::setMovementBounds(const Lore::Vector2 &min,
                               const Lore::Vector2 &max)
{
    m_minBounds = min;
    m_maxBounds = max;

    m_maxBounds.x -= m_sprite.getBounds().getWidth();
}


//Callbacks
void Bomber::setOnBombDroppedCallback(const BombDroppedCallback &callback)
{
    m_bombDroppedCallback = callback;
}

void Bomber::setOnAllBombsDroppedCallback(const AllBombsDroppedCallback &callback)
{
    m_allBombsDroppedCallback = callback;
}


////////////////////////////////////////////////////////////////////////////////
// Getters                                                                    //
////////////////////////////////////////////////////////////////////////////////
int Bomber::getTurnNumber() const
{
    return m_turnNumber;
}


int Bomber::getTurnBombsCount() const
{
    return m_turnBombs;
}

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
    //COWTODO: Clean up.
    constexpr int kSpriteFrames = 3;

    //
    m_sprite.loadTexture("Bomber.png");
    m_frameIndex = 0;

    //Get the Frame Properties.
    auto rect   = m_sprite.getSourceRectangle();
    auto frameW = rect.getWidth () / kSpriteFrames;
    auto frameH = rect.getHeight();

    //Create the Frames Rectangles.
    m_spriteFrames.reserve(kSpriteFrames);

    for(int i = 0; i < kSpriteFrames; ++i)
    {
        Lore::Rectangle frameRect(i * frameW, 0, frameW, frameH);
        m_spriteFrames.push_back(frameRect);
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
    m_dropSpot = m_random.next(m_minBounds.x, m_maxBounds.x);
    m_speed.x  = (m_dropSpot < m_sprite.getPosition().x) ? -200 : +200;
}

void Bomber::dropBomb()
{
    //Dropped all bombs?
    if(m_bombsRemaining == 0)
    {
        m_isDroppingBombs = false;
        m_allBombsDroppedCallback();

        cout << "All bombs has been dropped" << endl;
        changeSpriteFrame(kFrameIndex_Sad);
        return;
    }

    //Update the bombs stats.
    --m_bombsRemaining;
    ++m_bombsDropped;

    //COWTODO: Fix to correct offset.
    m_bombDroppedCallback(m_sprite.getPosition());

    cout << "Bomb dropped" << endl;
}
