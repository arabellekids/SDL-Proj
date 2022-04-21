#include "_Objects.h"
#include "../Game.h"
#include "../TextureManager.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams) : GameObject(pParams)
{
    m_x = pParams->getX();
    m_y = pParams->getY();
    m_w = pParams->getW();
    m_h = pParams->getH();
    
    m_texID = pParams->getTexID();

    m_curRow = 1;
    m_curFrame = 1;
}

void SDLGameObject::draw()
{
    TextureManager::Instance()->drawFrame(m_texID, m_x,m_y, \
    m_w,m_h, m_curRow,m_curFrame, Game::Instance()->getRenderer());
}

void SDLGameObject::update() {}
void SDLGameObject::clean() {}
