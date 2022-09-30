//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        MenuScene.h                               //
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

#ifndef __Game_Kaboom_include_MenuScene_h__
#define __Game_Kaboom_include_MenuScene_h__

//Game_Kaboom
#include "GameKaboom_Utils.h"
#include "GameBackground.h"
#include "Bomb.h"

NS_GAMEKABOOM_BEGIN

class MenuScene : public Lore::Scene
{
    // CTOR / DTOR //
public:
    MenuScene();


    // Update / Draw / Handle Events //
public:
    virtual void update(float dt) override;
    virtual void draw()           override;


    // Inits //
private:
    void initStuff();


    // Private Methods //
private:
    void changeSelection(int delta, bool playSound = true);
    void onBombExplode();


    // iVars //
private:
    GameBackground m_background;

    //Title
    Lore::Text m_titleTop;
    Lore::Text m_titleBottom;

    //Play / Credits
    Lore::Text m_playText;
    Lore::Text m_creditsText;

    //AmazingCow
    Lore::Text m_amazingcowText;

    //Bomb
    Bomb m_bomb;
    int  m_selectionIndex;
};

NS_GAMEKABOOM_END
#endif // __Game_Kaboom_include_MenuScene_h__ //
