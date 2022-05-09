#include <SDL2/SDL.h>
#include "_Objects.h"

AnimatedGraphic::AnimatedGraphic() : \
SDLGameObject()
{
}

void AnimatedGraphic::load(const LoaderParams* pParams)
{
    SDLGameObject::load(pParams);
    m_animSpeed = pParams->getAnimSpeed();
}

void AnimatedGraphic::update()
{
    m_curFrame = (SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames;
}

void AnimatedGraphic::draw()
{
    SDLGameObject::draw();
}

void AnimatedGraphic::clean() {}