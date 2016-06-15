//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        BombManager.cpp                           //
//            █ █        █ █        Game_Kaboom                               //
//             ████████████                                                   //
//           █              █       Copyright (c) 2016                        //
//          █     █    █     █      AmazingCow - www.AmazingCow.com           //
//          █     █    █     █                                                //
//           █              █       N2OMatt - n2omatt@amazingcow.com          //
//             ████████████         www.amazingcow.com/n2omatt                //
//                                                                            //
//                  This software is licensed as GPLv3                        //
//                 CHECK THE COPYING FILE TO MORE DETAILS                     //
//                                                                            //
//    Permission is granted to anyone to use this software for any purpose,   //
//   including commercial applications, and to alter it and redistribute it   //
//               freely, subject to the following restrictions:               //
//                                                                            //
//     0. You **CANNOT** change the type of the license.                      //
//     1. The origin of this software must not be misrepresented;             //
//        you must not claim that you wrote the original software.            //
//     2. If you use this software in a product, an acknowledgment in the     //
//        product IS HIGHLY APPRECIATED, both in source and binary forms.     //
//        (See opensource.AmazingCow.com/acknowledgment.html for details).    //
//        If you will not acknowledge, just send us a email. We'll be         //
//        *VERY* happy to see our work being used by other people. :)         //
//        The email is: acknowledgment_opensource@AmazingCow.com              //
//     3. Altered source versions must be plainly marked as such,             //
//        and must not be misrepresented as being the original software.      //
//     4. This notice may not be removed or altered from any source           //
//        distribution.                                                       //
//     5. Most important, you must have fun. ;)                               //
//                                                                            //
//      Visit opensource.amazingcow.com for more open-source projects.        //
//                                                                            //
//                                  Enjoy :)                                  //
//----------------------------------------------------------------------------//

//Header
#include "BombManager.h"
//std
#include <algorithm>

//Usings
USING_NS_GAMEKABOOM;


////////////////////////////////////////////////////////////////////////////////
// Constants                                                                  //
////////////////////////////////////////////////////////////////////////////////
const char * const kSoundName_Dropping   = "bomb.wav";
const char * const kSoundName_ExplodeFmt = "bomb_explode%d.wav";
const char * const kSoundName_Caught     = "bomb_caught.wav";

constexpr int kSoundExplode_Count = 1;


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
BombManager::BombManager()
{
    initSounds();
}

BombManager::~BombManager()
{
    //Empty...
}



// Update / Draw //
void BombManager::update(float dt)
{
    for(auto &bomb : m_bombsVec)
        bomb->update(dt);
}

void BombManager::draw()
{
    for(auto &bomb : m_bombsVec)
        bomb->draw();
}


////////////////////////////////////////////////////////////////////////////////
// Actions                                                                    //
////////////////////////////////////////////////////////////////////////////////
void BombManager::reset(const TurnInfo &turnInfo)
{
    m_turnInfo         = turnInfo;
    m_aliveBombs       = 0;
    m_bombsCaught      = 0;
    m_isExplodingBombs = false;

    //Create the needed bombs for this level.
    for(int i = 0; i < m_turnInfo.bombsCount - (int)m_bombsVec.size(); ++i)
        createBombHelper();

    //Reset them.
    resetAllBombs();
}

void BombManager::dropBombAt(const Lore::Vector2 &pos)
{
    playDroppingEffect();

    for(auto &bomb : m_bombsVec)
    {
        if(bomb->getState() == Bomb::State::Dead)
        {
            bomb->setPosition(pos);
            bomb->startDropping();
            m_aliveBombs++;

            break;
        }
    }
}

void BombManager::checkCollision(Paddle &paddle)
{
    if(m_isExplodingBombs)
        return;

    for(auto &bomb : m_bombsVec)
    {
        //Dead bomb.
        if(bomb->getState() != Bomb::State::Alive)
            continue;

        //Did not collide with paddle.
        if(!paddle.checkCollision(bomb->getHitBox()))
            continue;


        //Did collide with paddle.
        //Kill the bomb, update the housekeep vars
        //and inform the listeners
        bomb->kill();

        ++m_bombsCaught;
        --m_aliveBombs;

        m_onBombCaughtCallback();

        //Play Sound.
        playCaughtEffect();

        //Check if Player won this level and inform the listeners.
        if(m_bombsCaught == m_turnInfo.bombsCount)
        {
            stopDroppingEffect();
            m_onAllBombsCaughtCallback();
        }
    }
}


////////////////////////////////////////////////////////////////////////////////
// Setters                                                                    //
////////////////////////////////////////////////////////////////////////////////
//Movement
void BombManager::setBombMovementBounds(int maxY)
{
    m_maxBombY = maxY;
}

 //Callbacks
void BombManager::setOnBombCaughtCallback(const BombCaughtCallback &callback)
{
    m_onBombCaughtCallback = callback;
}

void BombManager::setOnAllBombsCaughtCallback(const AllBombsCaughtCallback &callback)
{
    m_onAllBombsCaughtCallback = callback;
}


void BombManager::setOnBombReachTargetCallback(const BombReachTargetCallback &callback)
{
    m_onBombReachTargetCallback = callback;
}

void BombManager::setOnBombExplodeCallback(const BombExplodeCallback &callback)
{
    m_onBombExplodeCallback = callback;
}

void BombManager::setOnAllBombsExplodedCallback(const AllBombsExplodedCallback &callback)
{
    m_onAllBombsExplodedCallback = callback;
}


////////////////////////////////////////////////////////////////////////////////
// Private Methods                                                            //
////////////////////////////////////////////////////////////////////////////////
void BombManager::createBombHelper()
{
    auto bomb = std::unique_ptr<Bomb>(new Bomb());
    bomb->setMovementBounds(m_maxBombY);

    auto explode = COREGAME_CALLBACK_0(BombManager::onBombExplodeFinished, this);
    auto reach   = COREGAME_CALLBACK_0(BombManager::onBombReachTarget,     this);

    bomb->setOnReachTargetCallback    (reach);
    bomb->setOnExplodeFinishedCallback(explode);

    m_bombsVec.push_back(std::move(bomb));
}

void BombManager::explodeNextBomb()
{
    Bomb *lowerBomb = nullptr;

    for(auto &bomb : m_bombsVec)
    {
        //Bomb isn't alive... - Do not interest us.
        if(bomb->getState() != Bomb::State::Alive)
            continue;

        //Edge case - There is not lower bomb yet...
        if(!lowerBomb)
        {
            lowerBomb = bomb.get();
            continue;
        }

        //Current bomb is at bottom of the "current" lower bomb.
        if(bomb->getPosition().y > lowerBomb->getPosition().y)
            lowerBomb = bomb.get();
    }

    //There is any bomb to explode?
    if(lowerBomb)
    {
        lowerBomb->explode();
        playExplodeEffect();
        m_onBombExplodeCallback();
    }
}

void BombManager::stopAllBombs()
{
    stopDroppingEffect();

    for(auto &bomb : m_bombsVec)
        bomb->stopDropping();
}

void BombManager::resetAllBombs()
{
    for(auto &bomb : m_bombsVec)
        bomb->reset(m_turnInfo);
}


////////////////////////////////////////////////////////////////////////////////
// Sound Effects                                                              //
////////////////////////////////////////////////////////////////////////////////
void BombManager::initSounds()
{
    //Init the sounds.
    auto soundMgr = Lore::SoundManager::instance();

    //Dropping
    soundMgr->loadEffect(kSoundName_Dropping);

    //Caught
    soundMgr->loadEffect(kSoundName_Caught);

    //Exploded
    for(int i = 0; i < kSoundExplode_Count; ++i)
    {
        auto name = CoreGame::StringUtils::format(kSoundName_ExplodeFmt, i);
        soundMgr->loadEffect(name);
    }
}

void BombManager::playDroppingEffect()
{
    if(!m_isPlayingDroppingEffect)
    {
        KABOOM_DLOG("BombManager::playDroppingEffect - Start Playing");

        m_isPlayingDroppingEffect = true;

        Lore::SoundManager::instance()->playEffect(
            kSoundName_Dropping,
            Lore::SoundManager::kPlayForever
        );
    }
}

void BombManager::stopDroppingEffect()
{
    m_isPlayingDroppingEffect = false;
    Lore::SoundManager::instance()->stopEffect(kSoundName_Dropping);
}


void BombManager::playCaughtEffect()
{
    Lore::SoundManager::instance()->playEffect(kSoundName_Caught);
}

void BombManager::playExplodeEffect()
{
    auto name = CoreGame::StringUtils::format(kSoundName_ExplodeFmt, 0);
    Lore::SoundManager::instance()->playEffect(name);
}

////////////////////////////////////////////////////////////////////////////////
// Bombs Callbacks                                                            //
////////////////////////////////////////////////////////////////////////////////
void BombManager::onBombReachTarget()
{
    KABOOM_DLOG("BombManager::onBombReachTarget - Bomb reach target");

    m_onBombReachTargetCallback();

    m_isExplodingBombs = true;
    stopAllBombs();

    //Start exploding the bombs.
    explodeNextBomb();
}

void BombManager::onBombExplodeFinished()
{
    KABOOM_DLOG("BombManager::onBombExplodeFinished - Bomb Explode Finished");

    --m_aliveBombs;
    if(m_aliveBombs == 0)
        m_onAllBombsExplodedCallback();
    else
        explodeNextBomb();
}
