//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        GameBackground.cpp                        //
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
#include "GameBackground.h"
//Game
#include "Game_Constants.h"

//Usings
USING_NS_GAMEKABOOM;


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
GameBackground::GameBackground()
{
    setNormalColor();
}

////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
void GameBackground::draw()
{
    //COWTODO: Clean this up.
    auto winMgr   = Lore::WindowManager::instance();
    auto renderer = winMgr->getRenderer();

    SDL_Rect skyRect = {
                0,
                0,
                winMgr->getWindowWidth(),
                kSize_SkyHeight
             };

    SDL_Rect groundRect = {
                0,
                kSize_SkyHeight,
                winMgr->getWindowWidth(),
                winMgr->getWindowHeight() - kSize_SkyHeight
            };


    SDL_SetRenderDrawColor(renderer, m_skyColor.r,
                                     m_skyColor.g,
                                     m_skyColor.b,
                                     m_skyColor.a);
    SDL_RenderFillRect(renderer, &skyRect);

    SDL_SetRenderDrawColor(renderer, m_groundColor.r,
                                     m_groundColor.g,
                                     m_groundColor.b,
                                     m_groundColor.a);
    SDL_RenderFillRect(renderer, &groundRect);
}

void GameBackground::explode()
{
    auto gm = Lore::GameManager::instance();

    m_skyColor.setRGBA(gm->getRandomNumber(0, 255),
                       gm->getRandomNumber(0, 255),
                       gm->getRandomNumber(0, 255));

    m_groundColor.setRGBA(gm->getRandomNumber(0, 255),
                          gm->getRandomNumber(0, 255),
                          gm->getRandomNumber(0, 255));
}

void GameBackground::setNormalColor()
{
    m_skyColor.setRGBA   (0x70, 0x92, 0xBE);
    m_groundColor.setRGBA(0x52, 0x7E, 0x2D);
}
