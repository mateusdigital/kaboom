#ifndef __Game_Kaboom_include_GameBackground_h__
#define __Game_Kaboom_include_GameBackground_h__

//Game_Kaboom
#include "GameKaboom_Utils.h"


NS_GAMEKABOOM_BEGIN

class GameBackground
{
    // CTOR / DTOR //
public:
    GameBackground();

    // Public Methods //
public:
     void draw();

     void explode();
     void setNormalColor();

     // iVars //
private:
    Lore::Color m_skyColor;
    Lore::Color m_groundColor;
};

NS_GAMEKABOOM_END
#endif // __Game_Kaboom_include_GameBackground_h__ //
