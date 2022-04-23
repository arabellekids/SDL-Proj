#ifndef __TEXTUREMANAGER__
#define __TEXTUREMANAGER__

#include <SDL2/SDL.h>
#include <map>
#include <string>

class TextureManager
{
public:
    // Loads a texture from a file
    bool load(std::string filename,std::string id, SDL_Renderer* pRenderer);
    
    // Draws an entire texture
    void draw(std::string id, int x,int y, int width,int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    
    // Draws a frame from a texture
    void drawFrame(std::string id, int x,int y, int w,int h, int curRow,int curFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    static TextureManager* Instance()
    {
        if(s_pInstance == NULL)
        {
            s_pInstance = new TextureManager();
        }
        return s_pInstance;
    }
private:
    TextureManager() {}
    ~TextureManager() {}
    
    static TextureManager* s_pInstance;
    std::map<std::string, SDL_Texture*> m_textureMap;
};

#endif