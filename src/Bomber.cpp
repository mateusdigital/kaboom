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
    m_frameIndex(0),
    //Movement / Bounds
    m_speed    (Lore::Vector2::Zero()),
    m_minBounds(Lore::Vector2::Zero()),
    m_maxBounds(Lore::Vector2::Zero()),
    //Turn / Bombs
    m_turnNumber     (0),
    m_turnBombs      (0),
    m_bombsDropped   (0),
    m_bombsRemaining (0),
    m_isDroppingBombs(0),
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
    m_sprite.move(m_speed * dt);
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

}

void Bomber::setMovementBounds(const Lore::Vector2 &min,
                               const Lore::Vector2 &max)
{

}


//Callbacks
void Bomber::setOnBombDroppedCallback(const BombDroppedCallback &callback)
{

}

void Bomber::setOnAllBombsDroppedCallback(const AllBombsDroppedCallback &callback)
{

}


////////////////////////////////////////////////////////////////////////////////
// Getters                                                                    //
////////////////////////////////////////////////////////////////////////////////
int Bomber::getTurnNumber() const
{

}


int Bomber::getTurnBombsCount() const
{

}

int Bomber::getTurnBombsDroppedCount() const
{

}

int Bomber::getTurnBombsRemainingCount() const
{

}


bool Bomber::isDroppingBombs() const
{

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
    m_sprite.setSourceRectangle(m_spriteFrames[m_frameIndex]);
}
