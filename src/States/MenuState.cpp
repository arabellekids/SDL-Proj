#include <iostream>
#include "MenuState.h"
#include "PlayState.h"
#include "../TextureManager.h"
#include "../Game.h"

const std::string MenuState::s_menuID = "MENU";

void MenuState::update()
{
    for(std::vector<GameObject*>::size_type i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}

void MenuState::render()
{
    for(std::vector<GameObject*>::size_type i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool MenuState::onEnter()
{
    // Load the play button img
    if(!TextureManager::Instance()->load("assets/PlayButtonSheet.png", "PlayButton", Game::Instance()->getRenderer()))
    {
        return false;
    }

    // Load the exit button img
    if(!TextureManager::Instance()->load("assets/ExitButtonSheet.png", "ExitButton", Game::Instance()->getRenderer()))
    {
        return false;
    }

    GameObject* button1 = new MenuButton(
        new LoaderParams(100,100,400,100, "PlayButton"),
        s_menuToPlay);
    GameObject* button2 = new MenuButton(
        new LoaderParams(100,300,400,100, "ExitButton"),
        s_exitFromMenu);
    
    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);

    std::cout << "Entering MenuState\n";
    return true;
}

bool MenuState::onExit()
{
    for(std::vector<GameObject*>::size_type i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    
    m_gameObjects.clear();
    TextureManager::Instance()->clearTex("PlayButton");
    TextureManager::Instance()->clearTex("ExitButton");
    
    std::cout << "Exiting MenuState\n";
    return true;
}

void MenuState::s_menuToPlay()
{
    std::cout << "Play button clicked!\n";
    Game::Instance()->getStateMachine()->changeState(new PlayState());
    //std::cout << "Changed State!\n";
}
void MenuState::s_exitFromMenu()
{
    std::cout << "Exit button clicked!\n";
    Game::Instance()->quit();
}
