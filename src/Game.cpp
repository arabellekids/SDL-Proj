#include <iostream>
#include <SDL2/SDL_image.h>
#include "Game.h"


bool Game::init(const char* title, int xpos,int ypos, int width,int height, bool fullscreen)
{
    int flags = SDL_WINDOW_RESIZABLE;
    
    // Fullscreen is enabled
    if(fullscreen)
    {
	flags = SDL_WINDOW_FULLSCREEN;
    }
    
    // Init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        // SDL failed to init
        std::cout << "SDL init failed...\n";
        return false;
    }
    
    std::cout << "SDL init success...\n";
    
    // Init the window
    m_pWindow = SDL_CreateWindow(title, xpos,ypos, width,height, flags);
    
    if (m_pWindow == 0)
    {
        // Failed to create the window
        std::cout << "Window creation failed...\n";
        return false;
    }
    
    std::cout << "Window creation success!\n";
    
    // Create the renderer
    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
    
    if (m_pRenderer == 0)
    {
        // Failed to create the renderer
        std::cout << "Renderer creation failed...\n";
        return false;
    }
    
    std::cout << "Renderer creation success!\n";
    
    // Clear the render color to white
    SDL_SetRenderDrawColor(m_pRenderer, 255,255,255,255);
    
    std::cout << "Init success!\n";
    
    // Run the game
    m_bRunning = true;

    // Load the image
    m_texManager.load("assets/goku_punch_anim.png", "Goku", m_pRenderer);
    
    // Initialization finished
    return true;
}

void Game::render()
{
	// Clear the renderer to the draw color
	SDL_RenderClear(m_pRenderer);
	
    // Draw the static texture
    m_texManager.draw("Goku", 0,0, 68,54, m_pRenderer);

    // Draw the animated texture
    m_texManager.drawFrame("Goku", 100,100, 68,54, 1,m_curFrame, m_pRenderer);

	// Draw to the screen
	SDL_RenderPresent(m_pRenderer);
}

void Game::clean()
{
	std::cout << "Cleaning game...\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

void Game::handleEvents()
{
	SDL_Event event;
	if(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			// Quit the game
			case SDL_QUIT:
				m_bRunning = false;
			break;
			
			default:
			break;
		}
	}
}

void Game::update()
{
    m_curFrame = ((int)SDL_GetTicks() / 100) % 5;
}
