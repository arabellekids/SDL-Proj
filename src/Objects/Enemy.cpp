#include <SDL2/SDL.h>
#include "_Objects.h"

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{
}

void Enemy::draw()
{
    SDLGameObject::draw();
}

void Enemy::update()
{
    m_x += 1;
    m_curFrame = (SDL_GetTicks() / 100) % 5;
}

void Enemy::clean() {}