//Header
#include "SplashScene.h"
//Game_Kaboom
#include "GameScene.h"
#include "MenuScene.h"

//Usings
USING_NS_GAMEKABOOM


// Load / Unload //
void SplashScene::load()
{
    Lore::WindowManager::instance()->setClearColor(Lore::Color::White());

    initSprites();
    initTimers ();
}

void SplashScene::unload()
{
    //Empty...
}


// Update / Draw / Handle Events //
void SplashScene::update(float dt)
{
    //Update the timers.
    m_appearTimer.update   (dt);
    m_disappearTimer.update(dt);
}

void SplashScene::draw()
{
    m_logoSprite.draw();
}


// Inits //
void SplashScene::initSprites()
{
    auto winCenter = Lore::WindowManager::instance()->getWindowRect().getCenter();

    //Logo Sprite
    m_logoSprite.loadTexture("AmazingCow_Logo.png");
    m_logoSprite.setOrigin(Lore::ITransformable::OriginHelpers::Center());
    m_logoSprite.setPosition(winCenter);
    m_logoSprite.setIsVisible(false);
}

void SplashScene::initTimers()
{
    m_disappearTimer.setInterval(1.5f);
    m_disappearTimer.setRepeatCount(1);
    m_disappearTimer.setTickCallback([this]() {
        KABOOM_DLOG("m_disapperTimer - done....");
        auto gm = Lore::GameManager::instance();
        gm->changeScene(std::unique_ptr<Lore::Scene>(new MenuScene()));
    });

    m_appearTimer.setInterval(0.5f);
    m_appearTimer.setRepeatCount(1);
    m_appearTimer.setTickCallback([this]() {
        m_logoSprite.setIsVisible(true);
        m_disappearTimer.start();
    });
    m_appearTimer.start();
}
