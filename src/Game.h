#ifndef __GAME__
#define __GAME__

#include <iostream>
#include <SDL2/SDL.h>

#include <vector>
#include "Objects/_Objects.h"
#include "States/GameStateMachine.h"

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
    void quit() { m_bRunning = false; }

    // function to get the private running variable
    bool running() const { return m_bRunning; }

    // Function to get the private SDL_Renderer
    SDL_Renderer* getRenderer() const { return m_pRenderer; }
    GameStateMachine* getStateMachine() const { return m_pGameStateMachine; }

private:
    Game(){}

    static Game* s_pInstance;

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    GameStateMachine* m_pGameStateMachine;

    std::vector<GameObject*> m_gameObjects;
    
    bool m_bRunning;
};

#endif
