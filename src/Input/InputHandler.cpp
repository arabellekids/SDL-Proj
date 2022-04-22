#include <iostream>
#include "InputHandler.h"
#include "../Game.h"

InputHandler* InputHandler::s_pInstance = NULL;

// Initializes all connected joysticks
void InputHandler::initJoysticks()
{
    // Joystick sub system not yet inited
    if(SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
    {
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }

    // No joysticks to init
    if(SDL_NumJoysticks() <= 0)
    {
        m_bJoysticksInited = false;
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
    m_bJoysticksInited = true;

    std::cout << "Initialized " << m_joysticks.size() << " joystick(s)\n";
}

// Closes all opened joysticks
void InputHandler::clean()
{
    // Joysticks havent been initialized yet
    if(!m_bJoysticksInited) { return; }

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
        // Quit
        if(event.type == SDL_QUIT)
        {
            Game::Instance()->quit();
        }

        // Button down
        if(event.type == SDL_JOYBUTTONDOWN)
        {
            int joyID = event.jaxis.which;
            m_joyButtonStates[joyID][event.jbutton.button] = true;
        }
        // Button up
        if(event.type == SDL_JOYBUTTONUP)
        {
            int joyID = event.jaxis.which;
            m_joyButtonStates[joyID][event.jbutton.button] = false;
        }

        // Joystick movement
        if(event.type == SDL_JOYAXISMOTION)
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
    }
}

float InputHandler::joy_xvalue(int joy, int stick)
{
    if(m_joystickValues.size() > 0)
    {
        // Left stick
        if(stick == 1)
        {
            return m_joystickValues[joy].first->getX();
        }
        // Right stick
        else if(stick == 2)
        {
            return m_joystickValues[joy].second->getX();
        }
    }
    return 0;
}

float InputHandler::joy_yvalue(int joy, int stick)
{
    if(m_joystickValues.size() > 0)
    {
        // Left stick
        if(stick == 1)
        {
            return m_joystickValues[joy].first->getY();
        }
        // Right stick
        else if(stick == 2)
        {
            return m_joystickValues[joy].second->getY();
        }
    }
    return 0;
}