#include "_States.h"
#include "../Game.h"
#include "../TextureManager.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::update()
{
    for(std::vector<GameObject*>::size_type i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}

void GameOverState::render()
{
    for(std::vector<GameObject*>::size_type i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool GameOverState::onEnter()
{
    if(!TextureManager::Instance()->load("assets/GameOverSheet.png","GameOverText", Game::Instance()->getRenderer()))
    {
        return false;
    }
    if(!TextureManager::Instance()->load("assets/MenuButtonSheet.png","MenuButton", Game::Instance()->getRenderer()))
    {
        return false;
    }
    if(!TextureManager::Instance()->load("assets/RestartButtonSheet.png","RestartButton", Game::Instance()->getRenderer()))
    {
        return false;
    }

    GameObject* gameOverText = new AnimatedGraphic(
        new LoaderParams(200,100,190,30, "GameOverText"),
        2,2);
    GameObject* button1 = new MenuButton(
        new LoaderParams(200,200,200,80, "MenuButton"),
        s_gameOverToMain);
    GameObject* button2 = new MenuButton(
        new LoaderParams(200,300,200,80, "RestartButton"),
        s_restartPlay);
    
    m_gameObjects.push_back(gameOverText);
    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);
    
    std::cout << "Entering GameOverState\n";

    return true;
}

bool GameOverState::onExit()
{
    // Clean the objects
    for(std::vector<GameObject*>::size_type i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();

    // Remove the loaded textures
    TextureManager::Instance()->clearTex("GameOverText");
    TextureManager::Instance()->clearTex("MenuButton");
    TextureManager::Instance()->clearTex("RestartButton");

    std::cout << "Exiting GameOverState\n";
    return true;
}

void GameOverState::s_gameOverToMain()
{
    Game::Instance()->getStateMachine()->changeState(new MenuState());
}
void GameOverState::s_restartPlay()
{
    Game::Instance()->getStateMachine()->changeState(new PlayState());
}