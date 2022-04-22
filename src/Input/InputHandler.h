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

    int xvalue(int joy, int stick);
    int yvalue(int joy, int stick);

private:
    InputHandler() {}
    ~InputHandler() {}

    static InputHandler* s_pInstance;

    std::vector<SDL_Joystick*> m_joysticks;
    std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;

    bool m_bJoysticksInited;
    const int m_joyDeadZone = 10000;
};
typedef InputHandler TheInputHandler;

#endif