#ifndef __Game_Kaboom_include_MenuScene_h__
#define __Game_Kaboom_include_MenuScene_h__

//Lore
#include "Lore.h"
//Game_Kaboom
#include "GameKaboom_Utils.h"

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
    void initSprites();
    void initTexts  ();


    // iVars //
private:
    Lore::Sprite m_logoSprite;
    Lore::Sprite m_bombSprite;
    Lore::Sprite m_amazingCowSprite;

    // Lore::Text m_playText;
    // Lore::Text m_creditsText;

    int m_selectedIndex;
};

NS_GAMEKABOOM_END
#endif // __Game_Kaboom_include_MenuScene_h__ //
