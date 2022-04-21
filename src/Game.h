#ifndef __GAME__
#define __GAME__

#include <SDL2/SDL.h>

class Game
{
public:
    Game(){}
    ~Game(){}

    bool init(const char* title,
    int xpos, int ypos,
    int width, int height,
    bool fullscreen=false);
    
    void render();
    void update();
    void handleEvents();
    void clean();

    // function to get the private running variable
    bool running() { return m_bRunning; }

private:
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    SDL_Texture* m_pTexture; // The new SDL_Texture variable
    SDL_Rect m_srcRect; // The source rectangle
    SDL_Rect m_destRect; // The destination rectangle

    bool m_bRunning;
};

#endif
