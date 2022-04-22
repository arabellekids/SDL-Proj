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
        if(event.type == SDL_JOYAXISMOTION)
        {
            //std::cout << "Joystick Moved! Value=" << event.jaxis.value <<  "\n";
            int joyID = event.jaxis.which;

            switch(event.jaxis.axis)
            {
                // Left stick left-right
                case 0:
                    if(event.jaxis.value > m_joyDeadZone)
                    {
                        m_joystickValues[joyID].first->setX(1);
                    }
                    else if(event.jaxis.value < -m_joyDeadZone)
                    {
                        m_joystickValues[joyID].first->setX(-1);
                    }
                    else
                    {
                        m_joystickValues[joyID].first->setX(0);
                    }   
                break;

                // Left stick up-down
                case 1:
                    if(event.jaxis.value > m_joyDeadZone)
                    {
                        m_joystickValues[joyID].first->setY(1);
                    }
                    else if(event.jaxis.value < -m_joyDeadZone)
                    {
                        m_joystickValues[joyID].first->setY(-1);
                    }
                    else
                    {
                        m_joystickValues[joyID].first->setY(0);
                    }   
                break;

                // Right stick left-right
                case 3:
                    if(event.jaxis.value > m_joyDeadZone)
                    {
                        m_joystickValues[joyID].second->setX(1);
                    }
                    else if(event.jaxis.value < -m_joyDeadZone)
                    {
                        m_joystickValues[joyID].second->setX(-1);
                    }
                    else
                    {
                        m_joystickValues[joyID].second->setX(0);
                    }   
                break;

                // Right stick up-down
                case 4:
                    if(event.jaxis.value > m_joyDeadZone)
                    {
                        m_joystickValues[joyID].second->setY(1);
                    }
                    else if(event.jaxis.value < -m_joyDeadZone)
                    {
                        m_joystickValues[joyID].second->setY(-1);
                    }
                    else
                    {
                        m_joystickValues[joyID].second->setY(0);
                    }   
                break;

                default:
                break;
            }
        }
    }
}

int InputHandler::xvalue(int joy, int stick)
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

int InputHandler::yvalue(int joy, int stick)
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