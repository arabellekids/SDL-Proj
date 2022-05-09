#include "_States.h"
#include "../Factory/StateParser.h"
#include "../Game.h"
#include "../TextureManager.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::setCallbacks(const std::vector<Callback>& callbacks)
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

void PauseState::s_pauseToMain()
{
    // Remove Pause State
    Game::Instance()->getStateMachine()->popState();
    // Remove Play State
    Game::Instance()->getStateMachine()->popState();
    // Add Menu State
    Game::Instance()->getStateMachine()->pushState(new MainMenuState());
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
    // Parse the state
    StateParser stateParser;
    stateParser.parseState("test.xml", s_pauseID, &m_gameObjects, &m_texIDList);

    m_callbacks.push_back(nullptr); // Pushback nullptr calbackID to start from 1
    m_callbacks.push_back(s_pauseToMain);
    m_callbacks.push_back(s_resumePlay);

    // Set the callbacks for menu items
    setCallbacks(m_callbacks);

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

    // Clear the loaded textures from the texture manager
    for(std::vector<std::string>::size_type i = 0; i < m_texIDList.size(); i++)
    {
        TextureManager::Instance()->clearTex(m_texIDList[i]);
    }
    m_texIDList.clear();
    
    std::cout << "Exiting MenuState\n";
    return true;
}