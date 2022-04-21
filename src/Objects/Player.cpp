#include "Player.h"

void Player::load(int x,int y, int width, int height, std::string texID)
{
    GameObject::load(x,y, width,height, texID);
}

void Player::draw(SDL_Renderer* pRenderer)
{
    GameObject::draw(pRenderer);
}

void Player::update()
{
    m_x -= 1;
}