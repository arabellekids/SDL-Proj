#include <SDL2/SDL.h>
#include "_Objects.h"
#include "../Input/InputHandler.h"
#include "../Game.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams)
{
    m_curFrame = 0;
}

void Player::draw()
{
    SDLGameObject::draw();
}

void Player::update()
{
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