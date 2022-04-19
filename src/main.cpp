#include <SDL2/SDL.h>

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

bool Init(const char* title, int xpos,int ypos,
int width,int height,
int flags=SDL_WINDOW_SHOWN)
{
    // Init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        // SDL failed to init
        return false;
    }
    
    // Create window
    g_pWindow = SDL_CreateWindow(title, xpos,ypos, width,height, flags);
    
    if (g_pWindow == 0)
    {
        // Failed to create window
        return false;
    }
    
    // Create renderer
    g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
    
    // Initialization finished
    return true;
}

void Render()
{
    // Set current color to black
    SDL_SetRenderDrawColor(g_pRenderer, 0,0,0,255);
    
    // Clear the window to the color (Black)
    SDL_RenderClear(g_pRenderer);
    
    // Display the window
    SDL_RenderPresent(g_pRenderer);
}

int main()
{
    if (!Init("Setting up SDL",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 640,480) )
    {
        // Failed to init
        return 1;
    }
    
    Render();
    
    SDL_Delay(5000);
    SDL_Quit();
    return 0;
}
