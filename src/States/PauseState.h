#ifndef __PAUSESTATE__
#define __PAUSESTATE__

#include <vector>
#include "GameState.h"
#include "../Objects/_Objects.h"

class PauseState : public GameState
{
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();
    
    virtual std::string getStateID() const { return s_pauseID; }

private:
    // Callback functions for menu items
    static void s_pauseToMain();
    static void s_resumePlay();
    
    static const std::string s_pauseID;
    std::vector<GameObject*> m_gameObjects;
};

#endif