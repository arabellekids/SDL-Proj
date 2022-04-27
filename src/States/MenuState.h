#ifndef __MENUSTATE__
#define __MENUSTATE__

#include <vector>
#include "GameState.h"
#include "../Objects/_Objects.h"

class MenuState : public GameState
{
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();
    
    virtual std::string getStateID() const { return s_menuID; }

private:
    // Callback functions for menu items
    static void s_menuToPlay();
    static void s_exitFromMenu();
    
    static const std::string s_menuID;
    std::vector<GameObject*> m_gameObjects;
};

#endif