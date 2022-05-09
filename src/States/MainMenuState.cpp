#include <iostream>
#include "_States.h"
#include "../Factory/StateParser.h"
#include "../TextureManager.h"
#include "../Game.h"

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
{
    // Loop through the game objects
    for(std::vector<GameObject*>::size_type i = 0; i < m_gameObjects.size(); i++)
    {
        // If they are of type MenuButton then assign  their callbacks
        if(dynamic_cast<MenuButton*>(m_gameObjects[i]))
        {
            MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}

void MainMenuState::update()
{
    for(std::vector<GameObject*>::size_type i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}

void MainMenuState::render()
{
    for(std::vector<GameObject*>::size_type i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool MainMenuState::onEnter()
{
    // Parse the state
    StateParser stateParser;
    stateParser.parseState("test.xml", s_menuID, &m_gameObjects, &m_texIDList);

    m_callbacks.push_back(nullptr); // Pushback nullptr calbackID to start from 1
    m_callbacks.push_back(s_menuToPlay);
    m_callbacks.push_back(s_exitFromMenu);

    // Set the callbacks for menu items
    setCallbacks(m_callbacks);

    std::cout << "Entering MenuState\n";
    return true;
}

bool MainMenuState::onExit()
{
    for(std::vector<GameObject*>::size_type i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    
    m_gameObjects.clear();

    // Clear the loaded textures from the texture manager
    for(std::vector<std::string>::size_type i = 0; i < m_texIDList.size(); i++)
    {
        TextureManager::Instance()->clearTex(m_texIDList[i]);
    }
    m_texIDList.clear();
    
    std::cout << "Exiting MenuState\n";
    return true;
}

void MainMenuState::s_menuToPlay()
{
    std::cout << "Play button clicked!\n";
    Game::Instance()->getStateMachine()->changeState(new PlayState());
}
void MainMenuState::s_exitFromMenu()
{
    std::cout << "Exit button clicked!\n";
    Game::Instance()->quit();
}
