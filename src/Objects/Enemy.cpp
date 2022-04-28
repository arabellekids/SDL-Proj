#include <SDL2/SDL.h>
#include "_Objects.h"
#include "../Input/InputHandler.h"

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{
    m_curFrame = 0;
    m_vel.setY(2);
    m_vel.setX(0.001);
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