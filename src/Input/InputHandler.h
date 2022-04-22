#ifndef __INPUTHANDLER__
#define __INPUTHANDLER__

#include <SDL2/SDL.h>
#include <vector>
#include "../Math/Vector2D.h"

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

    float xvalue(int joy, int stick);
    float yvalue(int joy, int stick);

    bool getButtonState(int joy, int buttonNum)
    {
        if(m_buttonStates.size() == 0){ return false; }
        return m_buttonStates[joy][buttonNum];
    }

private:
    InputHandler() {}
    ~InputHandler() {}

    static InputHandler* s_pInstance;

    std::vector<SDL_Joystick*> m_joysticks;
    std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
    std::vector<std::vector<bool>> m_buttonStates;

    bool m_bJoysticksInited;
    const float m_joyDeadZone = 0.2f;
};
typedef InputHandler TheInputHandler;

#endif
