#include <iostream>

#include "_States.h"
#include "../Factory/StateParser.h"
#include "../Input/InputHandler.h"
#include "../TextureManager.h"
#include "../Game.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
    {
        Game::Instance()->getStateMachine()->pushState(new PauseState());
        return;
    }
    
    // Update the objects
    for(std::vector<GameObject*>::size_type i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }

    // Check for collision between the player and the enemy
    if(checkCollision(
    dynamic_cast<SDLGameObject*>(m_gameObjects[0]),
    dynamic_cast<SDLGameObject*>(m_gameObjects[1])))
    {
        Game::Instance()->getStateMachine()->changeState(new GameOverState());
        return;
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
    // Parse the state
    StateParser stateParser;
    stateParser.parseState("test.xml", s_playID, &m_gameObjects, &m_texIDList);

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

    // Clear the loaded textures from the texture manager
    for(std::vector<std::string>::size_type i = 0; i < m_texIDList.size(); i++)
    {
        TextureManager::Instance()->clearTex(m_texIDList[i]);
    }
    m_texIDList.clear();

    std::cout << "Exiting PlayState\n";
    return true;
}

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    // Sides of rect A
    leftA = p1->getPos().getX();
    rightA = leftA + p1->getW();
    topA = p1->getPos().getY();
    bottomA = topA + p1->getH();

    // Sides of rect B
    leftB = p2->getPos().getX();
    rightB = leftB + p2->getW();
    topB = p2->getPos().getY();
    bottomB = topB + p2->getH();
    
    // If any of the sides from A are outside B
    if( bottomA <= topB ){ return false; }
    if( topA >= bottomB ){ return false; }
    if( rightA <= leftB ){ return false; }
    if( leftA >= rightB ){ return false; }
    
    // Collided
    return true;
}