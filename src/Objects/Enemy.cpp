#include <SDL2/SDL.h>
#include "_Objects.h"
#include "../Input/InputHandler.h"

Enemy::Enemy() : SDLGameObject()
{ 
}

void Enemy::load(const LoaderParams* pParams)
{
    SDLGameObject::load(pParams);
    m_vel.setY(2);
}

void Enemy::draw()
{
    SDLGameObject::draw();
}

void Enemy::update()
{
    if(m_pos.getY() < 0) { m_vel.setY(2); }
    else if(m_pos.getY() > 400) { m_vel.setY(-2); }
    SDLGameObject::update();
}

void Enemy::clean() {}