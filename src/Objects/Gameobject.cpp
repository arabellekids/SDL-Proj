#include "GameObject.h"
#include "../TextureManager.h"

void GameObject::load(int x,int y, int width,int height, std::string texID)
{
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
    m_texID = texID;

    m_curRow = 1;
    m_curFrame = 1;
}

void GameObject::draw(SDL_Renderer* pRenderer)
{
    TheTexManager::Instance()->drawFrame(m_texID, m_x,m_y, m_width,m_height, \
    m_curRow,m_curFrame, pRenderer);
}

void GameObject::update()
{
    m_x += 1;
}