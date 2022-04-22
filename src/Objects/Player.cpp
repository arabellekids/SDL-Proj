#include <SDL2/SDL.h>
#include "_Objects.h"
#include "../Input/InputHandler.h"
#include "../Game.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams)
{
}

void Player::draw()
{
    SDLGameObject::draw();
}

void Player::update()
{
    m_curFrame = (SDL_GetTicks() / 100) % 5;

    handleInput();
    SDLGameObject::update();
}

void Player::clean() {}

void Player::handleInput()
{
    m_vel.setX(0);
    m_vel.setY(0);
    
    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
    {
        m_vel.setX(2);
    }
    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
    {
        m_vel.setX(-2);
    }
    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
    {
        m_vel.setY(-2);
    }
    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
    {
        m_vel.setY(2);
    }
}