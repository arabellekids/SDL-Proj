#include <iostream>
#include "InputHandler.h"
#include "../Game.h"

InputHandler* InputHandler::s_pInstance = NULL;

InputHandler::InputHandler()
{
    m_bHasInited = false;
    m_keyStates = nullptr;
    
    m_mouseButtonStates.push_back(false); // Left mouse button
    m_mouseButtonStates.push_back(false); // Middle mouse button
    m_mouseButtonStates.push_back(false); // Right mouse button
}

// Initializes all connected joysticks
void InputHandler::initInput()
{
    // Joystick sub system not yet inited
    if(SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
    {
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }

    // No joysticks to init
    if(SDL_NumJoysticks() <= 0)
    {
        m_bHasInited = false;
        return;
    }

    // Init joysticks
    for(int i = 0; i < SDL_NumJoysticks(); i++)
    {
        SDL_Joystick* joy = SDL_JoystickOpen(i);
        // Add joystick to joystick list
        if(joy != NULL)
        {
            m_joysticks.push_back(joy);

            // Add the pair of joystick values
            m_joystickValues.push_back(std::make_pair(new Vector2D(0,0), new Vector2D(0,0)));

            // Add the button states
            std::vector<bool> tmpButtons;

            for(int j = 0; j < SDL_JoystickNumButtons(joy); j++)
            {
                tmpButtons.push_back(false);
            }
            m_joyButtonStates.push_back(tmpButtons);
        }
        else
        {
            // Failed to init joystick
            std::cout << SDL_GetError() << "\n";
        }
    }

    // Tell SDL to listen for joystick events
    SDL_JoystickEventState(SDL_ENABLE);
    m_bHasInited = true;

    std::cout << "Initialized " << m_joysticks.size() << " joystick(s)\n";
}

// Closes all opened joysticks
void InputHandler::clean()
{
    // Joysticks havent been initialized yet
    if(!m_bHasInited) { return; }

    // Close all the joysticks
    for(int i = 0; i < SDL_NumJoysticks(); i++)
    {
        SDL_JoystickClose(m_joysticks[i]);
    }
}

// Updates the input
void InputHandler::update()
{    
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        // Quit ////////////////
        case SDL_QUIT:
            Game::Instance()->quit();
        break;

        // Joystick input ////////////////
        case SDL_JOYAXISMOTION:
            onJoystickAxisMove(event);
        break;

        case SDL_JOYBUTTONDOWN:
            onJoystickButtonDown(event);
        break;

        case SDL_JOYBUTTONUP:
            onJoystickButtonUp(event);
        break;
        
        // Mouse input ////////////////
        case SDL_MOUSEMOTION:
            onMouseMove(event);
        break;

        case SDL_MOUSEBUTTONDOWN:
            onMouseButtonDown(event);
        break;

        case SDL_MOUSEBUTTONUP:
            onMouseButtonUp(event);
        break;
        
        // Keyboard input ////////////////
        case SDL_KEYDOWN:
            onKeyDown();
        break;

        case SDL_KEYUP:
            onKeyUp();
        break;
        
        default:
        break;

        }
    }
}

// Joystick input functions ////////////////

Vector2D* InputHandler::getJoyAxis(int joy, int stick)
{
    if(m_joystickValues.size() > 0)
    {
        // Left stick
        if(stick == 1)
        {
            return m_joystickValues[joy].first;
        }
        // Right stick
        else if(stick == 2)
        {
            return m_joystickValues[joy].second;
        }
    }
    return new Vector2D(0,0);
}

void InputHandler::onJoystickAxisMove(SDL_Event& event)
{
    int joyID = event.jaxis.which;
    float val = event.jaxis.value / (float)(SDL_JOYSTICK_AXIS_MAX);
    if(fabs(val) <= m_joyDeadZone) { val = 0; }
    
    switch(event.jaxis.axis)
    {
    // Left stick left-right
    case 0:
        m_joystickValues[joyID].first->setX(val);
    break;

    // Left stick up-down
    case 1:
        m_joystickValues[joyID].first->setY(val);
    break;

    // Right stick left-right
    case 3:
        m_joystickValues[joyID].second->setX(val);
    break;

    // Right stick up-down
    case 4:
        m_joystickValues[joyID].second->setY(val);
    break;

    default:
    break;
    }
}
void InputHandler::onJoystickButtonDown(SDL_Event& event)
{
    int joyID = event.jaxis.which;
    m_joyButtonStates[joyID][event.jbutton.button] = true;
}
void InputHandler::onJoystickButtonUp(SDL_Event& event)
{
    int joyID = event.jaxis.which;
    m_joyButtonStates[joyID][event.jbutton.button] = false;
}

// Mouse input functions ////////////////

void InputHandler::onMouseMove(SDL_Event& event)
{
    m_mousePos.setX(event.motion.x);
    m_mousePos.setY(event.motion.y);
}
void InputHandler::onMouseButtonDown(SDL_Event& event)
{
    // SDL mouse buttons are, 1=LEFT, 2=MIDDLE, 3=RIGHT
    m_mouseButtonStates[event.button.button-1] = true;
}
void InputHandler::onMouseButtonUp(SDL_Event& event)
{
    // SDL mouse buttons are, 1=LEFT, 2=MIDDLE, 3=RIGHT
    m_mouseButtonStates[event.button.button-1] = false;
}

// Keyboard input functions ////////////////

bool InputHandler::isKeyDown(SDL_Scancode key)
{
    if(m_keyStates == 0) { return false; }

    return (m_keyStates[key] == 1) ? true : false;
}
void InputHandler::onKeyDown()
{
    m_keyStates = SDL_GetKeyboardState(NULL);
}
void InputHandler::onKeyUp()
{
    m_keyStates = SDL_GetKeyboardState(NULL);
}
