//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        GAmeManager.h                             //
//            █ █        █ █        Lore                                      //
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

#ifndef __Lore_include_GameManager_h__
#define __Lore_include_GameManager_h__

//Lore
#include "Lore_Utils.h"
#include "Scene.h"


NS_LORE_BEGIN

class GameManager
{
    // Singleton //
public:
    COREGAME_SINGLETON_OF(GameManager);
    COREGAME_DISALLOW_COPY_MOVE_ASSIGNS(GameManager);
private:
    GameManager() {};


    // Init / Shutdown //
public:
    void initialize(int randomNumSeed, int targetFPS);
    void shutdown();


    // Scene Management //
public:
    void run(std::unique_ptr<Scene> scene);
    void changeScene(std::unique_ptr<Scene> scene);


    // Public Methods //
public:
    int  getRandomNumber(int min, int max);
    bool getRandomBool();

    int getTargetFPS() const;


    // Private Methods //
private:
    void update(float dt);
    void draw();
    void handleEvents();


    // iVars //
private:
    CoreRandom::Random m_random;

    int  m_targetFPS;
    bool m_running;

    std::unique_ptr<Scene> m_pScene;
};

NS_LORE_END
#endif // __Lore_include_GameManager_h__ //
