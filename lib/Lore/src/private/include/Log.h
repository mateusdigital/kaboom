//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Log.h                                     //
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

#ifndef __Lore_src_private_include_Log_h__
#define __Lore_src_private_include_Log_h__

//std
#include <cstdarg>
#include <string>

//Lore
#include "../../../include/Lore_Utils.h" //Public
#include "Lore_Private_Utils.h"          //Private


NS_LORE_BEGIN
NS_LORE_PVT_BEGIN

void _private_log(CoreGame::Log::Type logType,
                  const std::string &owner,
                  const char *fmt, ...);

NS_LORE_PVT_END
NS_LORE_END


////////////////////////////////////////////////////////////////////////////////
// Log Macros - DEBUG AND RELEASE                                             //
////////////////////////////////////////////////////////////////////////////////
#define PVT_LORE_LOG_DEBUG(_owner_, _fmt_, ...)                    \
    Lore::Lore_Private::_private_log(CoreGame::Log::Type::Debug4,  \
                                     _owner_,                      \
                                     _fmt_,                        \
                                     ##__VA_ARGS__)

#define PVT_LORE_LOG_ERROR(_owner_, _fmt_, ...)                  \
    Lore::Lore_Private::_private_log(CoreGame::Log::Type::Error, \
                                     _owner_,                    \
                                     _fmt_,                      \
                                     ##__VA_ARGS__)

#define PVT_LORE_LOG_WARNING(_owner_, _fmt_, ...)                  \
    Lore::Lore_Private::_private_log(CoreGame::Log::Type::Warning, \
                                     _owner_,                      \
                                     _fmt_,                        \
                                     ##__VA_ARGS__)


////////////////////////////////////////////////////////////////////////////////
// Log Macros - ONLY IN DEBUG                                                 //
////////////////////////////////////////////////////////////////////////////////
#if defined(LORE_RELEASE)
    #define PVT_LORE_DLOG_DEBUG(_owner_, _fmt_, ...)   do {} while(0)
    #define PVT_LORE_DLOG_ERROR(_owner_, _fmt_, ...)   do {} while(0)
    #define PVT_LORE_DLOG_WARNING(_owner_, _fmt_, ...) do {} while(0)

#else //defined(LORE_RELEASE)
    #define PVT_LORE_DLOG_DEBUG(_owner_, _fmt_, ...) \
        PVT_LORE_LOG_DEBUG(_owner_, _fmt_, ##__VA_ARGS__)

    #define PVT_LORE_DLOG_ERROR(_owner_, _fmt_, ...) \
        PVT_LORE_LOG_ERROR(_owner_, _fmt_, ##__VA_ARGS__)

    #define PVT_LORE_DLOG_WARNING(_owner_, _fmt_, ...) \
        PVT_LORE_LOG_WARNING(_owner_, _fmt_, ##__VA_ARGS__)

#endif //defined(LORE_RELEASE)

#endif // __Lore_src_private_include_Log_h__ //
