#include <iostream>
#include "PlayState.h"
#include "PauseState.h"
#include "../Objects/_Objects.h"
#include "../Input/InputHandler.h"
#include "../TextureManager.h"
#include "../Game.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
    {
        Game::Instance()->getStateMachine()->pushState(new PauseState());
    }
    
    else
    {
        // Update the objects
        for(std::vector<GameObject*>::size_type i = 0; i < m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->update();
        }
    }
}

void PlayState::render()
{
    // Draw the objects
    for(std::vector<GameObject*>::size_type i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool PlayState::onEnter()
{
    // Load the img
    if(!TextureManager::Instance()->load("assets/BlackShip2_Left.png","Ship",
    Game::Instance()->getRenderer()))
    {
        return false;
    }
    
    // Add the player
    GameObject* player = new Player(new LoaderParams(100,100,146,87, "Ship"));
    m_gameObjects.push_back(player);

    std::cout << "Entering PlayState\n";
    return true;
}

bool PlayState::onExit()
{
    // Clean the objects
    for(std::vector<GameObject*>::size_type i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();

    // Remove the loaded texture
    TextureManager::Instance()->clearTex("Ship");

    std::cout << "Exiting PlayState\n";
    return true;
}