//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        BombManager.h                             //
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

#ifndef __Game_Kaboom_include_BombManager_h__
#define __Game_Kaboom_include_BombManager_h__

//Lore
#include "Lore.h"
//Game_Kaboom
#include "GameKaboom_Utils.h"
#include "Bomb.h"
#include "Paddle.h"
#include "TurnInfo.h"


NS_GAMEKABOOM_BEGIN

class BombManager
{
    // Typedefs //
public:
    typedef std::function<void ()> BombCaughtCallback;
    typedef std::function<void ()> AllBombsCaughtCallback;

    typedef std::function<void ()> BombReachTargetCallback;

    typedef std::function<void ()> BombExplodeCallback;
    typedef std::function<void ()> AllBombsExplodedCallback;


    // CTOR / DTOR //
public:
    BombManager();
    ~BombManager();


    // Update / Draw //
public:
    void update(float dt);
    void draw();


    // Actions //
public:
    void reset(const TurnInfo &turnInfo);
    void dropBombAt(const Lore::Vector2 &pos);
    void checkCollision(Paddle &paddle);


    // Setters //
public:
    //Movement
    void setBombMovementBounds(int maxY);

    //Callbacks
    void setOnBombCaughtCallback    (const BombCaughtCallback     &callback);
    void setOnAllBombsCaughtCallback(const AllBombsCaughtCallback &callback);

    void setOnBombReachTargetCallback(const BombReachTargetCallback &callback);

    void setOnBombExplodeCallback     (const BombExplodeCallback      &callback);
    void setOnAllBombsExplodedCallback(const AllBombsExplodedCallback &callback);



    // Private Methods //
private:
    void createBombHelper();
    void explodeNextBomb();

    void stopAllBombs();
    void resetAllBombs();

    // Sounds Methods //
private:
    void initSounds();

    void playDroppingEffect();
    void stopDroppingEffect();

    void playCaughtEffect ();
    void playExplodeEffect();

    // Bombs Callbacks //
private:
    void onBombReachTarget();
    void onBombExplodeFinished();


    // iVars //
private:
    //Bombs
    std::vector<std::unique_ptr<Bomb>> m_bombsVec;

    //HouseKeep
    TurnInfo m_turnInfo;
    int      m_bombsCaught;
    int      m_aliveBombs;
    int      m_maxBombY;
    bool     m_isExplodingBombs;
    bool     m_isPlayingDroppingEffect;

    //Callbacks
    BombCaughtCallback       m_onBombCaughtCallback;
    AllBombsCaughtCallback   m_onAllBombsCaughtCallback;

    BombReachTargetCallback  m_onBombReachTargetCallback;

    BombExplodeCallback      m_onBombExplodeCallback;
    AllBombsExplodedCallback m_onAllBombsExplodedCallback;
};

NS_GAMEKABOOM_END
#endif // __Game_Kaboom_include_BombManager_h__ //
