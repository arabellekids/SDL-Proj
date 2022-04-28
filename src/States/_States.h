#ifndef __STATES__
#define __STATES__

#include <string>
#include <vector>

#include "../Objects/_Objects.h"

// The base GameState
class GameState
{
public:
    virtual void update() = 0;
    virtual void render() = 0;
    
    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;

    virtual std::string getStateID() const = 0;
    
    virtual ~GameState() {}
};

// The MenuState state
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

// The PauseState state
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

// The PlayState state
class PlayState : public GameState
{
    virtual void update();
    virtual void render();
    
    virtual bool onEnter();
    virtual bool onExit();
    
    virtual std::string getStateID() const { return s_playID; }
private:
    bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);
    static const std::string s_playID;
    std::vector<GameObject*> m_gameObjects;
};

// The GameOverState state
class GameOverState : public GameState
{
    virtual void update();
    virtual void render();
    
    virtual bool onEnter();
    virtual bool onExit();
    
    virtual std::string getStateID() const { return s_gameOverID; }
private:
    static void s_gameOverToMain();
    static void s_restartPlay();
    

    static const std::string s_gameOverID;
    std::vector<GameObject*> m_gameObjects;
};

#endif