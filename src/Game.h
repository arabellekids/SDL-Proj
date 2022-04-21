#ifndef __GAME__
#define __GAME__

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

#include "Objects/GameObject.h"

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

    GameObject* m_go;
    GameObject* m_player;
    GameObject* m_enemy;

    std::vector<GameObject*> m_gameObjects;
    
    bool m_bRunning;
};

#endif
