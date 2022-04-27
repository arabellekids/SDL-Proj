#include "PauseState.h"
#include "MenuState.h"
#include "../Game.h"
#include "../TextureManager.h"
#include "../Objects/_Objects.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::s_pauseToMain()
{
    // Remove Pause State
    Game::Instance()->getStateMachine()->popState();
    // Remove Play State
    Game::Instance()->getStateMachine()->popState();
    // Add Menu State
    Game::Instance()->getStateMachine()->pushState(new MenuState());
}
void PauseState::s_resumePlay()
{
    Game::Instance()->getStateMachine()->popState();
}

void PauseState::update()
{
    for(std::vector<GameObject*>::size_type i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}
void PauseState::render()
{
    for(std::vector<GameObject*>::size_type i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool PauseState::onEnter()
{
    if(!TextureManager::Instance()->load("assets/ResumeButtonSheet.png","ResumeButton",
    Game::Instance()->getRenderer()))
    {
        return false;
    }
    if(!TextureManager::Instance()->load("assets/MenuButtonSheet.png","MainButton",
    Game::Instance()->getRenderer()))
    {
        return false;
    }
    
    GameObject* button1 = new MenuButton(new LoaderParams(200,100,200,80,"MainButton"), s_pauseToMain);
    GameObject* button2 = new MenuButton(new LoaderParams(200,300,200,80,"ResumeButton"), s_resumePlay);
    
    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);

    std::cout << "Entering pause state\n";
    return true;
}
bool PauseState::onExit()
{
    for(std::vector<GameObject*>::size_type i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    TextureManager::Instance()->clearTex("MainButton");
    TextureManager::Instance()->clearTex("ResumeButton");
    
    std::cout << "Exiting MenuState\n";
    return true;
}