#ifndef __GAME__
#define __GAME__

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "Objects/_Objects.h"

// The Game class
class Game
{
public:
    // Gets the singleton instance
    static Game* Instance()
    {
        if(s_pInstance == NULL)
        {
            s_pInstance = new Game();
        }
        return s_pInstance;
    }
    
    bool init(const char* title,
    int xpos, int ypos,
    int width, int height,
    bool fullscreen=false);
    
    void render();
    void update();
    void handleEvents();
    void clean();
    void quit();

    // function to get the private running variable
    bool running() const { return m_bRunning; }

    // Function to get the private SDL_Renderer
    SDL_Renderer* getRenderer() const { return m_pRenderer; }

private:
    Game(){}

    static Game* s_pInstance;

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    std::vector<GameObject*> m_gameObjects;
    
    bool m_bRunning;
};

typedef Game TheGame;

#endif
