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
#include "Game_Constants.h"
#include "GameScene.h"
#include "CreditsScene.h"
#include "TurnInfo.h" //For bomb...

//Usings
USING_NS_GAMEKABOOM;


////////////////////////////////////////////////////////////////////////////////
// Load / Unload                                                              //
////////////////////////////////////////////////////////////////////////////////
void MenuScene::load()
{
    initStuff();
}

void MenuScene::unload()
{
    //Empty...
}


////////////////////////////////////////////////////////////////////////////////
// Update / Draw                                                              //
////////////////////////////////////////////////////////////////////////////////
void MenuScene::update(float dt)
{
    m_bomb.update(dt);

    auto inputMgr = Lore::InputManager::instance();

    if(inputMgr->isKeyClick(SDL_SCANCODE_UP))
    {
        changeSelection(-1);
    }
    else if(inputMgr->isKeyClick(SDL_SCANCODE_DOWN))
    {
        changeSelection(+1);
    }
    else if(inputMgr->isKeyClick(SDL_SCANCODE_RETURN))
    {
        auto gameMgr = Lore::GameManager::instance();
        if(m_selectionIndex == 0)
            gameMgr->changeScene(std::unique_ptr<Lore::Scene>(new GameScene()));
        else
            gameMgr->changeScene(std::unique_ptr<Lore::Scene>(new CreditsScene()));
    }
}

void MenuScene::draw()
{
    m_background.draw();

    //Title
    m_titleBottom.draw();
    m_titleTop.draw   ();

    //Play / Credits
    m_playText.draw   ();
    m_creditsText.draw();

    //Bomb
    m_bomb.draw();
}


////////////////////////////////////////////////////////////////////////////////
// Inits                                                                      //
////////////////////////////////////////////////////////////////////////////////
void MenuScene::initStuff()
{
    auto winRect   = Lore::WindowManager::instance()->getWindowRect();
    auto winCenter = winRect.getCenter();

    //Title
    m_titleTop.loadFont(kFontName, kFontSize_TitleText);
    m_titleTop.setOrigin(Lore::ITransformable::OriginHelpers::Center());
    m_titleTop.setPosition(
        Lore::Vector2::OffsetBy(winCenter, 0, -220)
    );
    m_titleTop.setString("Kaboom!");

    m_titleBottom.loadFont(kFontName, kFontSize_TitleText);
    m_titleBottom.setOrigin(m_titleTop.getOrigin());
    m_titleBottom.setPosition(
            Lore::Vector2::OffsetBy(m_titleTop.getPosition(), 0, 5)
    );
    m_titleBottom.setString("Kaboom!");
    m_titleBottom.setForegroundColor(Lore::Color::Black());


    //Play
    m_playText.loadFont(kFontName, kFontSize_PlayCreditsText);
    m_playText.setString("Play");
    m_playText.setPosition(
        winCenter.x - (m_playText.getBounds().getWidth() / 2),
        winCenter.y - 50
    );

    //Credits
    m_creditsText.loadFont(kFontName, kFontSize_PlayCreditsText);
    m_creditsText.setString("Credits");
    m_creditsText.setPosition(
        Lore::Vector2::OffsetBy(m_playText.getPosition(), 0, 80)
    );

    //Bomb
    TurnInfo info {

        .turnNumber  = 0,
        .bombsCount  = 0,
        .bombSpeed   = 0,
        .bomberSpeed = 0
    };

    m_bomb.reset(info);
    m_bomb.startDropping();
    m_bomb.setOnReachTargetCallback([](){});

    changeSelection(0); //Just to force the bomb position...
}

////////////////////////////////////////////////////////////////////////////////
// Private Methods                                                            //
////////////////////////////////////////////////////////////////////////////////
void MenuScene::changeSelection(int delta)
{
    m_selectionIndex = Lore::MathHelper::clamp(m_selectionIndex + delta, 0, 1);
    auto position    = (m_selectionIndex == 0)
                        ? m_playText.getPosition   ()
                        : m_creditsText.getPosition();

    m_bomb.setPosition(
        Lore::Vector2::OffsetBy(position, -40, -5)
    );
}
