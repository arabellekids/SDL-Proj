#include <iostream>
#include "GameStateMachine.h"

void GameStateMachine::update()
{
    if(!m_gameStates.empty())
    {
        // Call update on the last state
        m_gameStates.back()->update();
    }
}
void GameStateMachine::render()
{
    if(!m_gameStates.empty())
    {
        // Call render on the last state
        m_gameStates.back()->render();
    }
}

void GameStateMachine::pushState(GameState* pState)
{
    m_gameStates.push_back(pState);
    // Init the state
    m_gameStates.back()->onEnter();
}
void GameStateMachine::popState()
{
    // No game states to pop
    if(m_gameStates.empty()) { return; }
    
    // Try to exit
    if(m_gameStates.back()->onExit())
    {
        //delete m_gameStates.back();
        m_gameStates.pop_back();
    }
}
void GameStateMachine::changeState(GameState* pState)
{
    // Try to pop the last state
    if(!m_gameStates.empty())
    {
        // Dont change to the same state
        if(m_gameStates.back()->getStateID() == pState->getStateID())
        {
            return; // Dont change
        }
        if(m_gameStates.back()->onExit())
        {
            //delete m_gameStates.back();
            m_gameStates.pop_back();
        }
    }

    // Push back the new state
    m_gameStates.push_back(pState);
    // Init the state
    m_gameStates.back()->onEnter();
}