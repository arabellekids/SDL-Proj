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

    void initJoysticks();
    bool joysticksInited() { return m_bJoysticksInited; }

    float joy_xvalue(int joy, int stick);
    float joy_yvalue(int joy, int stick);

    bool getJoyButtonState(int joy, int buttonNum)
    {
        if(m_joyButtonStates.size() == 0){ return false; }
        return m_joyButtonStates[joy][buttonNum];
    }

private:
    InputHandler() {}
    ~InputHandler() {}

    static InputHandler* s_pInstance;

    std::vector<SDL_Joystick*> m_joysticks;
    std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;

    std::vector<std::vector<bool>> m_joyButtonStates;
    std::vector<bool> m_mouseButtonStates;

    bool m_bJoysticksInited;
    const float m_joyDeadZone = 0.35f;
};
typedef InputHandler TheInputHandler;

#endif
