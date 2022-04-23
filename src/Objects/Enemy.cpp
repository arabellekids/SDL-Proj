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
    m_curFrame = (SDL_GetTicks() / 100) % 5;
    
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

    SDLGameObject::update();
}

void Enemy::clean() {}