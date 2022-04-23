#ifndef __INPUTHANDLER__
#define __INPUTHANDLER__

#include <SDL2/SDL.h>
#include <vector>
#include "../Math/Vector2D.h"

enum XBOX360_buttons
{
    XBOXBUTTON_A = 0,
    XBOXBUTTON_B = 1,
    XBOXBUTTON_X = 2,
    XBOXBUTTON_Y = 3,
    XBOXBUTTON_LB = 4,
    XBOXBUTTON_RB = 5,
    XBOXBUTTON_BACK = 6,
    XBOXBUTTON_START = 7,
    XBOXBUTTON_XBOX = 8,
    XBOXBUTTON_LSTICK = 9,
    XBOXBUTTON_RSTICK = 10
};

enum Mouse_buttons
{
    MOUSE_LEFT = 0,
    MOUSE_MIDDLE = 1,
    MOUSE_RIGHT = 2
};

class InputHandler
{
public:
    static InputHandler* Instance()
    {
        if(s_pInstance == NULL)
        {
            s_pInstance = new InputHandler();
        }
        return s_pInstance;
    }

    void update();
    void clean();

    // Inits the connected joysticks
    void initInput();
    bool hasInitialized() { return m_bHasInited; }

    // Joystick input ////////////////

    // Returns the value of the joystick axis as a Vector2D*
    Vector2D* getJoyAxis(int joy, int stick);
    // Returns the joystick button state
    bool getJoyButton(int joy, int buttonNum)
    {
        if(m_joyButtonStates.size() == 0){ return false; }
        return m_joyButtonStates[joy][buttonNum];
    }

    // Mouse input ////////////////

    // Returns the mouse button state
    bool getMouseButton(int buttonNum)
    {
        return m_mouseButtonStates[buttonNum];
    }
    // Returns the mouse position
    Vector2D* getMousePos() { return m_mousePos; }
    
    // Keyboard input ////////////////

    // Returns if the given key is down
    bool isKeyDown(SDL_Scancode key);

private:
    InputHandler();
    ~InputHandler() {}

    static InputHandler* s_pInstance;
    bool m_bHasInited;

    // Joystick values
    const float m_joyDeadZone = 0.35f;
    std::vector<SDL_Joystick*> m_joysticks;
    std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
    std::vector<std::vector<bool>> m_joyButtonStates;

    // Mouse values
    std::vector<bool> m_mouseButtonStates;
    Vector2D* m_mousePos;

    // Keyboard values
    const Uint8* m_keyStates;

    // Private functions to handle different event types

    // Handle keyboard events
    void onKeyDown();
    void onKeyUp();

    // Handle mouse events
    void onMouseMove(SDL_Event& event);
    void onMouseButtonDown(SDL_Event& event);
    void onMouseButtonUp(SDL_Event& event);
    
    // Handle joystick events
    void onJoystickAxisMove(SDL_Event& event);
    void onJoystickButtonDown(SDL_Event& event);
    void onJoystickButtonUp(SDL_Event& event);
};

#endif
