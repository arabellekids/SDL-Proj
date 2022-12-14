#include "_States.h"
#include "../Factory/StateParser.h"
#include "../Game.h"
#include "../TextureManager.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
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
    // Parse the state
    StateParser stateParser;
    stateParser.parseState("test.xml", s_gameOverID, &m_gameObjects, &m_texIDList);

    m_callbacks.push_back(nullptr); // Pushback nullptr calbackID to start from 1
    m_callbacks.push_back(s_gameOverToMain);
    m_callbacks.push_back(s_restartPlay);

    // Set the callbacks for menu items
    setCallbacks(m_callbacks);
    
    std::cout << "Entering GameOverState\n";

    return true;
}

bool GameOverState::onExit()
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

    std::cout << "Exiting GameOverState\n";
    return true;
}

void GameOverState::s_gameOverToMain()
{
    Game::Instance()->getStateMachine()->changeState(new MainMenuState());
}
void GameOverState::s_restartPlay()
{
    Game::Instance()->getStateMachine()->changeState(new PlayState());
}