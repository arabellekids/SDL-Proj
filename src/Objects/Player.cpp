#include <SDL2/SDL.h>
#include "_Objects.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams)
{
}

void Player::draw()
{
    SDLGameObject::draw();
}

void Player::update()
{
    m_x -= 1;
    m_curFrame = (SDL_GetTicks() / 100) % 5;
}

void Player::clean() {}