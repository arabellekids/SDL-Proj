#ifndef __OBJECTS__
#define __OBJECTS__

#include "_LoaderParams.h"
#include "../Math/Vector2D.h"

// The base Gameobject class
class GameObject
{
public:
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;

    virtual void load(const LoaderParams* pParams) = 0;

protected:
    GameObject() {}
    virtual ~GameObject() {}
};

class BaseCreator
{
public:
    BaseCreator() {}
    virtual ~BaseCreator() {}
    virtual GameObject* createGameObject() const = 0;
};

//////////////// SDLGameObject ////////////////

// The SDLGameObject class
class SDLGameObject : public GameObject
{
public:
    SDLGameObject() {}

    virtual void draw();
    virtual void update();
    virtual void clean();
    
    virtual void load(const LoaderParams* pParams);

    Vector2D& getPos() { return m_pos; }
    Vector2D& getVel() { return m_vel; }
    Vector2D& getAccel() { return m_accel; }

    int getW() const { return m_w; }
    int getH() const { return m_h; }

protected:
    Vector2D m_pos;
    Vector2D m_vel;
    Vector2D m_accel;
    
    int m_w;
    int m_h;
    
    int m_curRow;
    int m_curFrame;

    int m_numFrames;
    
    std::string m_texID;
};

//////////////// Player ////////////////

// The Player class
class Player : public SDLGameObject
{
public:
    Player();

    virtual void draw();
    virtual void update();
    virtual void clean();

    virtual void load(const LoaderParams* pParams);
private:
    void handleInput();
};

// The Player Creator
class PlayerCreator : public BaseCreator
{
public:
    PlayerCreator() {}
    GameObject* createGameObject() const { return new Player(); }
};

//////////////// Enemy ////////////////

// The Enemy class
class Enemy : public SDLGameObject
{
public:
    Enemy();

    virtual void draw();
    virtual void update();
    virtual void clean();

    virtual void load(const LoaderParams* pParams);
};
// The Enemy Creator
class EnemyCreator : public BaseCreator
{
public:
    EnemyCreator() {}
    GameObject* createGameObject() const { return new Enemy(); }
};

//////////////// MenuButton ////////////////

// The MenuButton class
class MenuButton : public SDLGameObject
{
public:
    MenuButton();

    virtual void draw();
    virtual void update();
    virtual void clean();

    virtual void load(const LoaderParams* pParams);

    void setCallback(void(*callback) ()) { m_callback = callback; }
    int getCallbackID() { return m_callbackID; }
private:
    void(*m_callback) ();
    int m_callbackID;
    bool m_bReleased;

    enum button_state
    {
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        MOUSE_CLICKED = 2
    };
};
// The MenuButton Creator
class MenuButtonCreator : public BaseCreator
{
public:
    MenuButtonCreator() {}
    GameObject* createGameObject() const { return new MenuButton(); }
};

//////////////// AnimatedGraphic ////////////////

// The AnimatedGraphic class
class AnimatedGraphic : public SDLGameObject
{
public:
    AnimatedGraphic();

    virtual void draw();
    virtual void update();
    virtual void clean();

    virtual void load(const LoaderParams* pParams);
private:
    int m_animSpeed;
};
// The AnimatedGraphic Creator
class AnimatedGraphicCreator : public BaseCreator
{
public:
    AnimatedGraphicCreator() {}
    GameObject* createGameObject() const { return new AnimatedGraphic(); }
};

#endif