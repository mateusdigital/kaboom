//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        CoreGame_Verify.h                         //
//            █ █        █ █        CoreGame                                  //
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

#ifndef __CoreGame_include_Macros_CoreGame_Verify_h__
#define __CoreGame_include_Macros_CoreGame_Verify_h__

//CoreGame
#include "CoreGame_Assert.h"

////////////////////////////////////////////////////////////////////////////////
// NOTES                                                                      //
//                                                                            //
//   COW_VERIFY macro was heavily insipred on the amazing course by           //
//   Kenny Kerr - @kennykerr - PluralSight Modern C++ Libraries.              //
////////////////////////////////////////////////////////////////////////////////

// COREGAME_RELEASE - Release mode.
#if defined(COREGAME_RELEASE)
    #define COREGAME_VERIFY(_expr_) ((_expr_))

// !COREGAME_RELEASE - Debug mode.
#else
    ///@brief
    ///    Assert like macro that will behave like the assert in
    ///    non COREGAME_RELEASE builds, but unlike the assert it
    ///    WILL continue doing the check in COREGAME_RELEASE builds. \n
    ///    This is util in cases that we want an assert in debug, but
    ///    want that the expression being kept in the release builds.
    ///@param expr
    ///     The expression that will evaluated and will trigger the
    ///     assert if false in debug build. \n
    ///     Notice that it will be kept regardless if the build mode,
    ///     but will only trigger the assert in non COREGAME_RELEASE builds.
    #define COREGAME_VERIFY(_expr_)                    \
        COREGAME_ASSERT_ARGS(                          \
            (_expr_),                                  \
            "COREGAME_VERIFY Failed - expression(%s)", \
            #_expr_                                    \
        )

#endif // defined(COREGAME_RELEASE)

#endif // defined(__CoreGame_include_Macros_CoreGame_Verify_h__) //
