//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        CoreGame_Disallow.h                       //
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

#ifndef __CoreGame_include_Macros_CoreGame_Disallow_h__
#define __CoreGame_include_Macros_CoreGame_Disallow_h__


////////////////////////////////////////////////////////////////////////////////
// CTOR                                                                       //
////////////////////////////////////////////////////////////////////////////////
#define COREGAME_DISALLOW_CTOR(_type_) \
            _type_() = delete;


////////////////////////////////////////////////////////////////////////////////
// COPY / COPY ASSING                                                         //
////////////////////////////////////////////////////////////////////////////////
#define COREGAME_DISALLOW_COPY(_type_) \
            _type_(const _type_&) = delete;

#define COREGAME_DISALLOW_COPY_ASSIGN(_type_)\
            _type_& operator=(const _type_&) = delete;


////////////////////////////////////////////////////////////////////////////////
// MOVE / MOVE ASSIGN                                                         //
////////////////////////////////////////////////////////////////////////////////
#define COREGAME_DISALLOW_MOVE(_type_)  \
            _type_(_type_&&) = delete;

#define COREGAME_DISALLOW_MOVE_ASSIGN(_type_) \
            _type_& operator=(_type_&&) = delete;


////////////////////////////////////////////////////////////////////////////////
//                                                          //
////////////////////////////////////////////////////////////////////////////////

#define COREGAME_DISALLOW_CTOR_COPY_MOVE_ASSIGNS(_type_) \
            COREGAME_DISALLOW_CTOR(_type_)               \
            COREGAME_DISALLOW_COPY(_type_)               \
            COREGAME_DISALLOW_COPY_ASSIGN(_type_)        \
            COREGAME_DISALLOW_MOVE(_type_)               \
            COREGAME_DISALLOW_MOVE_ASSIGN(_type_)


#define COREGAME_DISALLOW_COPY_MOVE_ASSIGNS(_type_)    \
            /* Mo copy */                              \
            _type_(const _type_&) = delete;            \
            /* No assign */                            \
            _type_& operator=(const _type_&) = delete; \
            /* No move */                              \
            _type_(_type_&&) = delete;                 \
            /* No move-assign */                       \
            _type_& operator=(_type_&&) = delete;


#endif // defined(__CoreGame_include_Macros_CoreGame_Disallow_h__) //
