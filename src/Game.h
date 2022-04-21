#ifndef __GAME__
#define __GAME__

#include <SDL2/SDL.h>
#include "TextureManager.h"

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

    int m_curFrame;
    TextureManager m_texManager;

    bool m_bRunning;
};

#endif
