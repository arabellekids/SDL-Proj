#include <SDL2/SDL_image.h>
#include "TextureManager.h"

TextureManager* TextureManager::s_pInstance = NULL;

bool TextureManager::load(std::string filename,std::string id, SDL_Renderer* pRenderer)
{
    SDL_Surface* pTmpSurf = IMG_Load(filename.c_str());

    // Failed to load img
    if(pTmpSurf == NULL)
    {
        printf("Failed to load img %s at %s\n", id.c_str(), filename.c_str());
        return false;
    }

    // Convert surface to texture
    SDL_Texture* pTex = SDL_CreateTextureFromSurface(pRenderer, pTmpSurf);

    // Free the tmp surf
    SDL_FreeSurface(pTmpSurf);

    // Failed to create texture
    if(pTex == NULL)
    {
        printf("Failed to create texture for %s\n", id.c_str());
        return false;
    }

    // Finished loading, add the texture to the texture map
    m_textureMap[id] = pTex;
    
    printf("Finished loading texture %s at %s\n", id.c_str(), filename.c_str());
    return true;
}

void TextureManager::clearTex(std::string id)
{
    SDL_DestroyTexture(m_textureMap[id]);
    m_textureMap.erase(id);
}

void TextureManager::draw(std::string id, int x,int y, int width,int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    // Set up the rectangles
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    // Draw the texture
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect,&destRect, 0,NULL, flip);
}

void TextureManager::drawFrame(std::string id, int x,int y, int width,int height, int curRow,int curFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    // Set up the rectangles
    srcRect.x = width * curFrame;
    srcRect.y = height * (curRow - 1);
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    
    // Draw the texture
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect,&destRect, 0,NULL, flip);
}