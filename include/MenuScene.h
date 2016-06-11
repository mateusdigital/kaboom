#ifndef __Game_Kaboom_include_MenuScene_h__
#define __Game_Kaboom_include_MenuScene_h__

//Game_Kaboom
#include "GameKaboom_Utils.h"
#include "GameBackground.h"

NS_GAMEKABOOM_BEGIN

class MenuScene : public Lore::Scene
{
    // Load / Unload //
public:
    virtual void load  () override;
    virtual void unload() override;


    // Update / Draw / Handle Events //
public:
    virtual void update(float dt) override;
    virtual void draw()           override;


    // Inits //
private:
    void initStuff();

    // iVars //
private:
    GameBackground m_background;

    //Title
    Lore::Text m_titleTop;
    Lore::Text m_titleBottom;

    //AmazingCow
    Lore::Sprite m_cowLogo;
    Lore::Text   m_cowDesc;

    //Play msg
    Lore::Text m_playMsg;

    //Help msg
    Lore::Text m_helpMsg;
    Lore::Text m_help2Msg;
};

NS_GAMEKABOOM_END
#endif // __Game_Kaboom_include_MenuScene_h__ //
