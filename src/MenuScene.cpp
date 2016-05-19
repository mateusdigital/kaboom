//Header
#include "MenuScene.h"

//Usings
USING_NS_GAMEKABOOM;

// Load / Unload //
void MenuScene::load()
{
    Lore::WindowManager::instance()->setClearColor({255, 0, 0});

    initSprites();
    initTexts  ();
}
void MenuScene::unload()
{
    //Empty...
}


// Update / Draw / Handle Events //
void MenuScene::update(float dt)
{

}

void MenuScene::draw()
{
    m_logoSprite.draw();
    // m_bombSprite.draw();
    // m_amazingCowSprite.draw();

    // m_playText.draw();
    // m_creditsText.draw();
}


// Inits //
void MenuScene::initSprites()
{
    auto winW = Lore::WindowManager::instance()->getWindowWidth();

    //Logo Sprite
    m_logoSprite.loadTexture("Game_Logo.png");
    m_logoSprite.setOrigin(0.5, 0.5);
    m_logoSprite.setPosition(winW / 2, 100);
}
void MenuScene::initTexts()
{
    //"nokiafc22.tff"
}
