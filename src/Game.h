#ifndef __GAME__
#define __GAME__

#include <SDL2/SDL.h>
#include <iostream>

#include "Objects/Player.h"

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
    bool running()
    {
        return m_bRunning;
    }

private:
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    GameObject m_go;
    Player m_player;
    
    bool m_bRunning;
};

#endif
