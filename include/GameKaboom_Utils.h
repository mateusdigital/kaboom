
#ifndef __Game_Kaboom_include_GameKaboom_Utils_h__
#define __Game_Kaboom_include_GameKaboom_Utils_h__

#define NS_GAMEKABOOM_BEGIN namespace GameKaboom {
#define NS_GAMEKABOOM_END   }
#define USING_NS_GAMEKABOOM using namespace GameKaboom;


#include "CoreGame.h"

#define KABOOM_DLOG(_fmt_, ...) \
    COREGAME_DLOG(CoreGame::Log::Type::Debug1, (_fmt_), ##__VA_ARGS__)

#endif // __Game_Kaboom_include_GameKaboom_Utils_h__ //
