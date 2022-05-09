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
protected:
    std::vector<GameObject*> m_gameObjects;
    std::vector<std::string> m_texIDList;
};

// The Base MenuState state
class MenuState : public GameState
{
protected:
    typedef void(*Callback) ();
    virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;

    std::vector<Callback> m_callbacks;
};

// The MainMenuState state
class MainMenuState : public MenuState
{
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();
    
    virtual std::string getStateID() const { return s_menuID; }

private:
    virtual void setCallbacks(const std::vector<Callback>& callbacks);

    // Callback functions for menu items
    static void s_menuToPlay();
    static void s_exitFromMenu();
    
    static const std::string s_menuID;
};

// The PauseState state
class PauseState : public MenuState
{
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();
    
    virtual std::string getStateID() const { return s_pauseID; }

private:
    virtual void setCallbacks(const std::vector<Callback>& callbacks);

    // Callback functions for menu items
    static void s_pauseToMain();
    static void s_resumePlay();
    
    static const std::string s_pauseID;
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
};

// The GameOverState state
class GameOverState : public MenuState
{
    virtual void update();
    virtual void render();
    
    virtual bool onEnter();
    virtual bool onExit();
    
    virtual std::string getStateID() const { return s_gameOverID; }
private:
    virtual void setCallbacks(const std::vector<Callback>& callbacks);
    static void s_gameOverToMain();
    static void s_restartPlay();
    

    static const std::string s_gameOverID;
};

#endif