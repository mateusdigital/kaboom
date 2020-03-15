//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        CoreGame_Assert.h                         //
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

#ifndef __CoreGame_include_Macros_CoreGame_Assert_h__
#define __CoreGame_include_Macros_CoreGame_Assert_h__

// COREGAME_RELEASE - Release mode.
#if defined(COREGAME_RELEASE)
    #define COREGAME_ASSERT(_cond_, _msg_)           do {} while(0)
    #define COREGAME_ASSERT_ARGS(_cond_, _msg_, ...) do {} while(0)

// !COREGAME_RELEASE - Debug mode.
#else // defined(COREGAME_RELEASE) == false

    ///@brief
    ///    This function is only declared for !COREGAME_RELEASE,
    ///    this is what COREGAME_ASSERT and COREGAME_ASSERT_ARGS
    ///    will call.
    ///@warning DO NOT CALL IT DIRECTLY.
    ///@see COREGAME_ASSERT, COREGAME_ASSERT_ARGS
    void _coregame_assert_print_args(const char   *expr,
                                     const char   *file,
                                     unsigned int line,
                                     const char   *func,
                                     const char   *msg,
                                     ...);

    ///@brief
    ///     A more informative assert than the standard assert.
    ///@param
    ///     cond - The condition that will be asserted.
    ///@param
    ///     msg - The message the will be printed along the other info.
    ///@see
    ///     COREGAME_ASSERT_ARGS, COREGAME_VERIFY
    #define COREGAME_ASSERT(_cond_, _msg_)               \
                ((_cond_))                               \
                 ? (void) 0                              \
                 : _coregame_assert_print_args(#_cond_,  \
                                               __FILE__, \
                                               __LINE__, \
                                               __func__, \
                                               (_msg_));

    ///@brief
    ///    A more informative assert than the standard assert.
    ///@param
    ///    cond - The condition that will be asserted.
    ///@param
    ///    msg - The message the will be printed along the other info. \n
    ///          This can be used like a printf(3) format string.
    ///@param
    ///    ... - variadic arguments list that will be used to build the final
    ///          message. \n
    ///          This is used like the printf(3) var args list.
    ///@see
    ///    COREGAME_ASSERT, COREGAME_VERIFY
    #define COREGAME_ASSERT_ARGS(_cond_, _msg_, ...)         \
                ((_cond_))                                   \
                 ? (void) 0                                  \
                 : _coregame_assert_print_args(#_cond_,      \
                                               __FILE__,     \
                                               __LINE__,     \
                                               __func__,     \
                                               (_msg_),      \
                                               ##__VA_ARGS__)


#endif // defined(COREGAME_RELEASE)

#endif // defined(__CoreGame_include_Macros_CoreGame_Assert_h__) //
