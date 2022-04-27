#ifndef __PLAYSTATE__
#define __PLAYSTATE__

#include <vector>
#include "GameState.h"
#include "../Objects/_Objects.h"

class PlayState : public GameState
{
    virtual void update();
    virtual void render();
    
    virtual bool onEnter();
    virtual bool onExit();
    
    virtual std::string getStateID() const { return s_playID; }
private:
    static const std::string s_playID;
    std::vector<GameObject*> m_gameObjects;
};

#endif