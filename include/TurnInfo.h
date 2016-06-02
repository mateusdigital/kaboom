#ifndef __Game_Kaboom_include_TurnInfo_h__
#define __Game_Kaboom_include_TurnInfo_h__

//Game_Kaboom
#include "GameKaboom_Utils.h"

NS_GAMEKABOOM_BEGIN

struct TurnInfo
{
    int turnNumber;
    int bombsCount;
    int bombSpeed;
    int bomberSpeed;
};

NS_GAMEKABOOM_END
#endif // __Game_Kaboom_include_TurnInfo_h__ //
