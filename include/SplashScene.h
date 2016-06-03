#ifndef __Game_Kaboom_include_SplashScene_h__
#define __Game_Kaboom_include_SplashScene_h__

//Game_Kaboom
#include "GameKaboom_Utils.h"

NS_GAMEKABOOM_BEGIN

class SplashScene : public Lore::Scene
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
    void initSprites();
    void initTimers ();

    // iVars //
private:
    Lore::Sprite     m_logoSprite;
    CoreClock::Clock m_appearTimer;
    CoreClock::Clock m_disappearTimer;
};

NS_GAMEKABOOM_END
#endif // __Game_Kaboom_include_SplashScene_h__ //
