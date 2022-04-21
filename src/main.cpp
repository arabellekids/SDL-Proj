#include "Game.h"

int main(int argc, char* argv[])
{
    std::cout << "Starting Main...!\n";
    if(!Game::Instance()->init("SDL Window", 100,100, 640,480))
    {
        std::cout << "Game init failure - " << SDL_GetError() << "\n";
        return -1;
    }
    std::cout << "Game init success!\n";
    
    while ( Game::Instance()->running() )
    {
        Game::Instance()->handleEvents();
        Game::Instance()->update();
        Game::Instance()->render();

        SDL_Delay(10);
    }
    
    std::cout << "Game closing...\n";
    Game::Instance()->clean();
    
    return 0;
}
