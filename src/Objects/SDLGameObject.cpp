#include "_Objects.h"
#include "../Game.h"
#include "../TextureManager.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams) : \
m_pos(pParams->getX(), pParams->getY()), m_vel(0,0), m_accel(0,0)
{
    m_w = pParams->getW();
    m_h = pParams->getH();
    
    m_texID = pParams->getTexID();

    m_curRow = 1;
    m_curFrame = 1;
}

void SDLGameObject::draw()
{
    TextureManager::Instance()->drawFrame(m_texID,
    (int)m_pos.getX(), (int)m_pos.getY(),
    m_w,m_h, m_curRow,m_curFrame, Game::Instance()->getRenderer());
}

void SDLGameObject::update()
{
    m_vel += m_accel;
    m_pos += m_vel;
}
void SDLGameObject::clean() {}
