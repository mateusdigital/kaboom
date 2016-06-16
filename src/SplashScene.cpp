//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        SplashScene.cpp                           //
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
#include "SplashScene.h"
//Game_Kaboom
#include "GameScene.h"
#include "MenuScene.h"

//Usings
USING_NS_GAMEKABOOM


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
SplashScene::SplashScene()
{
    Lore::WindowManager::instance()->setClearColor(Lore::Color::White());

    initSprites();
    initTimers ();
}

////////////////////////////////////////////////////////////////////////////////
// Update / Draw                                                              //
////////////////////////////////////////////////////////////////////////////////
void SplashScene::update(float dt)
{
    //Update the timers.
    m_appearTimer.update   (dt);
    m_disappearTimer.update(dt);
}

void SplashScene::draw()
{
    m_logoSprite.draw();
}


////////////////////////////////////////////////////////////////////////////////
// Inits                                                                      //
////////////////////////////////////////////////////////////////////////////////
void SplashScene::initSprites()
{
    auto winCenter = Lore::WindowManager::instance()->getWindowRect().getCenter();

    //Logo Sprite
    m_logoSprite.loadTexture("AmazingCow_Logo.png");
    m_logoSprite.setOrigin(Lore::ITransformable::OriginHelpers::Center());
    m_logoSprite.setPosition(winCenter);
    m_logoSprite.setIsVisible(false);
}

void SplashScene::initTimers()
{
    m_disappearTimer.setInterval(1.5f);
    m_disappearTimer.setRepeatCount(1);
    m_disappearTimer.setTickCallback([this]() {
        KABOOM_DLOG("m_disapperTimer - done....");
        auto gm = Lore::GameManager::instance();
        gm->changeScene(std::unique_ptr<Lore::Scene>(new MenuScene()));
    });

    m_appearTimer.setInterval(0.5f);
    m_appearTimer.setRepeatCount(1);
    m_appearTimer.setTickCallback([this]() {
        m_logoSprite.setIsVisible(true);
        m_disappearTimer.start();
    });
    m_appearTimer.start();
}
