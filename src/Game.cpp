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
    SDL_Surface* pTmpSurface = IMG_Load("assets/goku_punch_anim.png");

    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTmpSurface);

    SDL_FreeSurface(pTmpSurface);

    // Set the source rect
    m_srcRect.x = 0;
    m_srcRect.y = 0;
    m_srcRect.w = 68;
    m_srcRect.h = 54;
    
    // Set the dest rect
    m_destRect.x = 0;
    m_destRect.y = 0;
    m_destRect.w = m_srcRect.w;
    m_destRect.h = m_srcRect.h;

    // Initialization finished
    return true;
}

void Game::render()
{
	// Clear the renderer to the draw color
	SDL_RenderClear(m_pRenderer);
	
    // Draw the texture
    SDL_RenderCopyEx(m_pRenderer, m_pTexture, &m_srcRect, &m_destRect, 45,NULL, SDL_FLIP_HORIZONTAL);

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
    m_srcRect.x = 68 * ( ((int)SDL_GetTicks() / 100) % 5 );
}
