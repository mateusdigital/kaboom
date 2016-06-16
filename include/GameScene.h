//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        GameScene.h                               //
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

#ifndef __Game_Kaboom_include_GameScene_h__
#define __Game_Kaboom_include_GameScene_h__

//Game_Kaboom
#include "GameKaboom_Utils.h"
#include "Bomber.h"
#include "BombManager.h"
#include "GameBackground.h"
#include "Paddle.h"


NS_GAMEKABOOM_BEGIN

class GameScene : public Lore::Scene
{
    // Enums //
public:
    enum class State
    {
        Playing,
        Paused,
        Victory,
        Defeat,
        GameOver
    };


    // CTOR / DTOR //
public:
    GameScene();


    // Update / Draw //
public:
    virtual void update(float dt) override;
    virtual void draw()           override;


    // Inits //
private:
    void initBomber();
    void initPaddle();
    void initBombs ();
    void initTexts ();
    void initSounds();


    // Texts Helpers //
private:
    void updateScoreText     ();
    void updateTurnNumberText();


    // Bomber / Bomb Manager Callbacks //
private:
    //Bomber
    void onBomberBombDropped(const Lore::Vector2 &pos);

    //Bombs
    void onBombCaught    ();
    void onAllBombsCaught();

    void onBombReachTarget();

    void onBombExplode     ();
    void onAllBombsExploded();


    // Others //
private:
    void resetTurn   ();
    void resetNewTurn();

    void checkCollisions();


    // Update Helpers //
private:
    void updateHelper_Playing (float dt);
    void updateHelper_Paused  (float dt);
    void updateHelper_Victory (float dt);
    void updateHelper_Defeat  (float dt);
    void updateHelper_GameOver(float dt);


    // Init Helpers //
private:
    void initHelper_Text(Lore::Text &text,
                         const std::string   &fontName, int fontSize,
                         const std::string   &str,
                         const Lore::Vector2 &origin,
                         const Lore::Vector2 &position);


    // Sound Helpers //
private:
    void soundHelper_Play(const std::string &name);
    void soundHelper_Stop(const std::string &name);
    void soundHelper_Unmute();
    void soundHelper_Mute  ();


    // Game State Helpers //
private:
    //Playing / Paused
    void gameStateHelper_PlayingToPaused();
    void gameStateHelper_PausedToPlaying();

    //Playing / Defeat
    void gameStateHelper_PlayingToDefeat();
    void gameStateHelper_DefeatToPlaying();

    //Playing / Victory
    void gameStateHelper_PlayingToVictory();
    void gameStateHelper_VictoryToPlaying();

    //Playing / GameOver
    void gameStateHelper_PlayingToGameOver();
    void gameStateHelper_GameOverToMenu   ();


    // iVars //
private:
    //GameObjects
    GameBackground m_background;
    Bomber         m_bomber;
    Paddle         m_paddle;
    BombManager    m_bombManager;

    //Texts
    Lore::Text       m_statusText;
    CoreClock::Clock m_statusBlinkTimer;

    Lore::Text m_scoreText;
    Lore::Text m_turnText;

    //HouseKepping
    int   m_turnNumber;
    int   m_score;
    State m_state;
};

NS_GAMEKABOOM_END
#endif // __Game_Kaboom_include_GameScene_h__ //
