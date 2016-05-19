#ifndef __Game_Kaboom_include_GameScene_h__
#define __Game_Kaboom_include_GameScene_h__

//Lore
#include "Lore.h"
//Game_Kaboom
#include "GameKaboom_Utils.h"
#include "Bomber.h"


NS_GAMEKABOOM_BEGIN

class GameScene : public Lore::Scene
{
    // Load / Unload //
public:
    virtual void load  () override;
    virtual void unload() override;


    // Update / Draw / Handle Events //
public:
    virtual void update(float dt) override;
    virtual void draw()           override;


    // Private Methods //
private:
    //Inits
    void initBomber();

    //Bomber Callbacks
    void onBomberBombDropped(const Lore::Vector2 &pos);
    void onBomberAllBombsDropped();

    // iVars //
private:
    Bomber m_bomber;
};

NS_GAMEKABOOM_END
#endif // __Game_Kaboom_include_GameScene_h__ //
