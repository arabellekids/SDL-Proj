#include <SDL2/SDL.h>
#include "_Objects.h"

AnimatedGraphic::AnimatedGraphic(const LoaderParams* pParams, int animSpeed, int numFrames) : \
SDLGameObject(pParams), m_animSpeed(animSpeed), m_numFrames(numFrames)
{
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