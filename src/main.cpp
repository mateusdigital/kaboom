//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        main.cpp                                  //
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

//Lore
#include "Lore.h"
//Game_Kaboom
#include "GameKaboom_Utils.h"
#include "SplashScene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "CreditsScene.h"

//Usings
USING_NS_GAMEKABOOM;


int main()
{
    Lore::ErrorControl::DieMode = Lore::ErrorControl::LORE_ERROR_DIE_ON_ALL_ERRORS;

    auto winMgr    = Lore::WindowManager::instance();
    auto assetsMgr = Lore::AssetsManager::instance();
    auto gameMgr   = Lore::GameManager::instance  ();
    auto inputMgr  = Lore::InputManager::instance ();
    auto soundMgr  = Lore::SoundManager::instance ();

    winMgr->initialize("Amazing Cow - Kaboom - v0.0.0",
                        800, 600,
                        800, 600,
                        0, 0);

    std::vector<std::string> paths = {
        "./assets",
        "/usr/local/share/amazingcow_game_kaboom/assets"
    };

    assetsMgr->initialize(paths);
    inputMgr->initialize();
    soundMgr->initialize(MIX_DEFAULT_FREQUENCY,
                         MIX_DEFAULT_FORMAT,
                         MIX_DEFAULT_CHANNELS,
                         2048);

    gameMgr->initialize(CoreRandom::Random::kRandomSeed, 60);

    gameMgr->run(std::unique_ptr<Lore::Scene>(new SplashScene()));

    winMgr->shutdown();
    gameMgr->shutdown();

    return 0;
}
