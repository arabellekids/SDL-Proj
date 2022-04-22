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
    // Joysticks not initialized
    if(!InputHandler::Instance()->joysticksInited()){ return; }

    // Xbox button is being pushed
    if(InputHandler::Instance()->getJoyButtonState(0, XBOXBUTTON_XBOX))
    {
        Game::Instance()->quit();
        return;
    }


    // Y is being pushed
    if(InputHandler::Instance()->getJoyButtonState(0, XBOXBUTTON_Y)) { return; }


    m_vel.setX(InputHandler::Instance()->joy_xvalue(0, 1) * 2);
    m_vel.setY(InputHandler::Instance()->joy_yvalue(0, 1) * 2);
}