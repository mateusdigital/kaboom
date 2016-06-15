//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        MenuScene.cpp                             //
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
#include "MenuScene.h"
//Game
#include "GameScene.h"
#include "Game_Constants.h"


//Usings
USING_NS_GAMEKABOOM;


// Load / Unload //
void MenuScene::load()
{
    initStuff();
}

void MenuScene::unload()
{
    //Empty...
}


// Update / Draw / Handle Events //
void MenuScene::update(float /* dt */)
{
    auto inputMgr = Lore::InputManager::instance();
    if(inputMgr->isKeyClick(SDL_SCANCODE_RETURN))
    {
        auto gameMgr = Lore::GameManager::instance();
        gameMgr->changeScene(std::unique_ptr<Lore::Scene>(new GameScene()));
    }
}

void MenuScene::draw()
{
    m_background.draw();

    //Title
    m_titleBottom.draw();
    m_titleTop.draw   ();

    //AmazingCow
    m_cowLogo.draw();
    m_cowDesc.draw();

    //Play / Help Message
    m_playMsg.draw();
    m_helpMsg.draw();
    m_help2Msg.draw();
}


// Inits //
void MenuScene::initStuff()
{
    auto winRect   = Lore::WindowManager::instance()->getWindowRect();
    auto winCenter = winRect.getCenter();

    //Title
    m_titleTop.loadFont(kFontName, kFontSize_TitleText);
    m_titleTop.setOrigin(Lore::ITransformable::OriginHelpers::Center());
    m_titleTop.setPosition(Lore::Vector2::OffsetBy(winCenter, 0, -220));
    m_titleTop.setString("Kaboom!");

    m_titleBottom.loadFont(kFontName, kFontSize_TitleText);
    m_titleBottom.setOrigin(m_titleTop.getOrigin());
    m_titleBottom.setPosition(
            Lore::Vector2::OffsetBy(m_titleTop.getPosition(), 0, 5)
    );
    m_titleBottom.setString("Kaboom!");
    m_titleBottom.setForegroundColor(Lore::Color::Black());


    //AmazingCow
    m_cowLogo.loadTexture("AmazingCow_Logo_Small.png");
    m_cowLogo.setOrigin(Lore::ITransformable::OriginHelpers::TopCenter());
    m_cowLogo.setPosition(winCenter.x,
                          m_titleBottom.getPosition().y +
                          m_titleBottom.getBounds().getSize().y);


    m_cowDesc.loadFont(kFontName, kFontSize_AmazingCowText);
    m_cowDesc.setOrigin(Lore::ITransformable::OriginHelpers::TopCenter());
    m_cowDesc.setPosition(winCenter.x,
                          m_cowLogo.getPosition().y +
                          m_cowLogo.getBounds().getSize().y + 20);
    m_cowDesc.setString("www.AmazingCow.com");


    //Play msg
    m_playMsg.loadFont(kFontName, kFontSize_PlayMessageText);
    m_playMsg.setOrigin(Lore::ITransformable::OriginHelpers::TopCenter());
    m_playMsg.setPosition(winCenter.x,
                          m_cowDesc.getPosition().y +
                          m_cowDesc.getBounds().getSize().y + 50);
    m_playMsg.setString("[Press ENTER to play]");


    //Help msg
    m_helpMsg.loadFont(kFontName, kFontSize_HelpMessageText);
    m_helpMsg.setOrigin(Lore::ITransformable::OriginHelpers::BottomCenter());
    m_helpMsg.setPosition(winCenter.x,
                          winRect.getHeight() - 50);
    m_helpMsg.setString("Help Instituto Ayrton Senna.");

    m_help2Msg.loadFont(kFontName, kFontSize_Help2MessageText);
    m_help2Msg.setOrigin(Lore::ITransformable::OriginHelpers::BottomCenter());
    m_help2Msg.setPosition(winCenter.x,
                           winRect.getHeight() - 20);
    m_help2Msg.setString("www.institutoayrtonsenna.org");
}
