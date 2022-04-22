#include <SDL2/SDL.h>
#include "_Objects.h"
#include "../Input/InputHandler.h"

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{
}

void Enemy::draw()
{
    SDLGameObject::draw();
}

void Enemy::update()
{
    m_vel.setX(InputHandler::Instance()->xvalue(0, 2) * 2);
    m_vel.setY(InputHandler::Instance()->yvalue(0, 2) * 2);
    
    m_curFrame = (SDL_GetTicks() / 100) % 5;

    SDLGameObject::update();
}

void Enemy::clean() {}