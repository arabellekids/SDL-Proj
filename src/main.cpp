#include "Game.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main()
{
    Uint32 frameStart, frameTime;

    std::cout << "Starting Main...!\n";
    if(!Game::Instance()->init("SDL Window", 100,100, 640,480))
    {
        std::cout << "Game init failure - " << SDL_GetError() << "\n";
        SDL_Delay(2000);
        return -1;
    }

    while ( Game::Instance()->running() )
    {
        frameStart = SDL_GetTicks();
    
        Game::Instance()->handleEvents();
        Game::Instance()->update();
        Game::Instance()->render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < DELAY_TIME)
        {
            SDL_Delay((int)(DELAY_TIME - frameTime));
        }
    }
    std::cout << "Game closing...\n";
    Game::Instance()->clean();
    return 0;
}
