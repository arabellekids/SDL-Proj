#include "_Objects.h"
#include "../Game.h"
#include "../TextureManager.h"

void SDLGameObject::load(const LoaderParams* pParams)
{
    m_pos = Vector2D(pParams->getX(),pParams->getY());
    m_w = pParams->getW();
    m_h = pParams->getH();
    
    m_vel = Vector2D(0,0);
    m_accel = Vector2D(0,0);

    m_texID = pParams->getTexID();
    m_curRow = 1;
    m_curFrame = 0;
    m_numFrames = pParams->getNumFrames();
}

void SDLGameObject::draw()
{
    if(m_vel.getX() >= 0)
    {
        TextureManager::Instance()->drawFrame(m_texID,
        (int)m_pos.getX(), (int)m_pos.getY(),
        m_w,m_h, m_curRow,m_curFrame, Game::Instance()->getRenderer());
    }
    else
    {
        TextureManager::Instance()->drawFrame(m_texID,
        (int)m_pos.getX(), (int)m_pos.getY(),
        m_w,m_h, m_curRow,m_curFrame, Game::Instance()->getRenderer(),
        SDL_FLIP_HORIZONTAL);
    }
}

void SDLGameObject::update()
{
    m_vel += m_accel;
    m_pos += m_vel;
}
void SDLGameObject::clean() {}
