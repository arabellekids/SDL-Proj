#ifndef __DEFAULTSTATE__
#define __DEFAULTSTATE__

#include "GameState.h"

class DefaultState : public GameState
{
    virtual void update() {}
    virtual void render() {}
    
    virtual bool onEnter() { return true; }
    virtual bool onExit() { return true; }
    
    virtual std::string getStateID() const { return "DefaultState"; }
};

#endif