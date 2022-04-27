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
    m_curFrame = 0;

    handleInput();
    SDLGameObject::update();
}

void Player::clean() {}

void Player::handleInput()
{   
    const Vector2D& target = InputHandler::Instance()->getMousePos();
    m_vel = target - m_pos;
    m_vel *= 0.02;
}