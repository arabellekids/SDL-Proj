#include "Game.h"

// Our Game object
Game* g_pGame = 0;

int main()
{
    g_pGame = new Game();
    g_pGame->init("SDL Window", 100,100, 640,480);
    
    while ( g_pGame->running() )
    {
        g_pGame->handleEvents();
        g_pGame->update();
        g_pGame->render();
    }
    
    g_pGame->clean();
    
    return 0;
}
