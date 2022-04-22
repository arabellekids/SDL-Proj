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

    // Inits joysticks
    void initJoysticks();
    bool joysticksInited() { return m_bJoysticksInited; }

    // Returns the x value of the joystick axis
    float joy_xvalue(int joy, int stick);
    // Returns the y value of the joystick axis
    float joy_yvalue(int joy, int stick);

    // Returns the joystick button state
    bool getJoyButtonState(int joy, int buttonNum)
    {
        if(m_joyButtonStates.size() == 0){ return false; }
        return m_joyButtonStates[joy][buttonNum];
    }

    // Returns the mouse button state
    bool getMouseButtonState(int buttonNum)
    {
        return m_mouseButtonStates[buttonNum];
    }
    // Returns the mouse position
    Vector2D* getMousePos() { return m_mousePos; }
    
    // Returns if the given key is down
    bool isKeyDown(SDL_Scancode key);

private:
    InputHandler();
    ~InputHandler() {}

    static InputHandler* s_pInstance;

    std::vector<SDL_Joystick*> m_joysticks;
    std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;

    std::vector<std::vector<bool>> m_joyButtonStates;
    std::vector<bool> m_mouseButtonStates;

    Vector2D* m_mousePos;
    const Uint8* m_keyStates;

    bool m_bJoysticksInited;
    const float m_joyDeadZone = 0.35f;
};
typedef InputHandler TheInputHandler;

#endif
