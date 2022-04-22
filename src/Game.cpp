//#include <iostream>
#include <SDL2/SDL_image.h>

#include "Game.h"
#include "TextureManager.h"
#include "Input/InputHandler.h"

Game* Game::s_pInstance = NULL;

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
    
    // Clear the window
    SDL_SetRenderDrawColor(m_pRenderer, 255,0,0,255);
    SDL_RenderClear(m_pRenderer);
    SDL_RenderPresent(m_pRenderer);

    // Run the game
    m_bRunning = true;
    
    //Load the texture
    if(!TextureManager::Instance()->load("assets/goku_punch_anim.png", "Goku", m_pRenderer))
    {
        return false;
    }

    m_gameObjects.push_back( new Player(new LoaderParams(100,100, 68,54, "Goku")) );
    m_gameObjects.push_back( new Enemy(new LoaderParams(300,300, 68,54, "Goku")) );
    
    std::cout << "Init success!\n";
    
    InputHandler::Instance()->initJoysticks();

    // Initialization finished
    return true;
}

void Game::render()
{
	// Clear the renderer to the draw color
	SDL_RenderClear(m_pRenderer);
	
    // Loop through the objects and draw them
    for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }

	// Draw to the screen
	SDL_RenderPresent(m_pRenderer);
}

// Cleans up all resources
void Game::clean()
{
	std::cout << "Cleaning game...\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
    InputHandler::Instance()->clean();

    // Loop through the objects and clean them
    for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    
    SDL_Delay(2000);
    SDL_Quit();
}

// Handles SDL events
void Game::handleEvents()
{
	InputHandler::Instance()->update();
}

void Game::update()
{
    // Loop through the objects and draw them
    for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}
