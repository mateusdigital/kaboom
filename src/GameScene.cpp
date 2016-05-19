//Header
#include "GameScene.h"

//Usings
USING_NS_GAMEKABOOM;


// Load / Unload //
void GameScene::load()
{

}

void GameScene::unload()
{
    //Empty...
}


// Update / Draw / Handle Events //
void GameScene::update(float dt)
{
    m_bomber.update(dt);
}

void GameScene::draw()
{
    m_bomber.draw();
}
