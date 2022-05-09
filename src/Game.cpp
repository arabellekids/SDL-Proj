//#include <iostream>
#include <SDL2/SDL_image.h>

#include "Game.h"
#include "TextureManager.h"
#include "Input/InputHandler.h"
#include "States/_States.h"
#include "Factory/GameObjectFactory.h"

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
    SDL_SetRenderDrawColor(m_pRenderer, 0,0,100,255);
    SDL_RenderClear(m_pRenderer);
    SDL_RenderPresent(m_pRenderer);
    
    // Register the object types
    GameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
    GameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
    GameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
    GameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());
    

    // Init the GameStateMachine
    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new MainMenuState());
    
    // Init input
    InputHandler::Instance()->initInput();
    
    // Initialization finished
    std::cout << "Init success!\n";
    m_bRunning = true;
    return true;
}

void Game::render()
{
	// Clear the renderer to the draw color
	SDL_RenderClear(m_pRenderer);
	
    // Call render on the GameStateMachine
    m_pGameStateMachine->render();

	// Draw to the screen
	SDL_RenderPresent(m_pRenderer);
}
void Game::update()
{
    // Call update on the GameStateMachine
    m_pGameStateMachine->update();
}

// Handles SDL events
void Game::handleEvents()
{
	InputHandler::Instance()->update();

    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
    {
        m_pGameStateMachine->changeState(new PlayState());
    }
}

// Cleans up all resources
void Game::clean()
{
	std::cout << "Cleaning game...\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
    InputHandler::Instance()->clean();

    //SDL_Delay(2000);
    SDL_Quit();
}
