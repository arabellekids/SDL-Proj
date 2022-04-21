#include "Enemy.h"

void Enemy::load(int x,int y, int width, int height, std::string texID)
{
    GameObject::load(x,y, width,height, texID);
}

void Enemy::draw(SDL_Renderer* pRenderer)
{
    GameObject::draw(pRenderer);
}

void Enemy::update()
{
    m_y += 1;
    m_x += 1;
    m_curFrame = (SDL_GetTicks() / 100) % 5;
}