#include <SDL2/SDL.h>
#include "_Objects.h"
#include "../Input/InputHandler.h"

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
    // Joysticks not initialized
    if(!InputHandler::Instance()->joysticksInited()){ return; }

    m_vel.setX(InputHandler::Instance()->xvalue(0, 1) * 2);
    m_vel.setY(InputHandler::Instance()->yvalue(0, 1) * 2);
}