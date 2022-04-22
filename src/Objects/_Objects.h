#ifndef __OBJECTS__
#define __OBJECTS__

#include "_LoaderParams.h"
#include "../Math/Vector2D.h"

// The base Gameobject class
class GameObject
{
public:
    virtual void draw()=0;
    virtual void update()=0;
    virtual void clean()=0;

protected:
    GameObject() {}
    //GameObject(const LoaderParams* pParams) {}
    virtual ~GameObject() {}
};

// The SDLGameObject class
class SDLGameObject : public GameObject
{
public:
    SDLGameObject(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();

protected:
    Vector2D m_pos;
    Vector2D m_vel;
    Vector2D m_accel;
    
    int m_w;
    int m_h;
    
    int m_curRow;
    int m_curFrame;
    
    std::string m_texID;
};

// The Player class
class Player : public SDLGameObject
{
public:
    Player(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();
private:
    void handleInput();
};

// The Enemy class
class Enemy : public SDLGameObject
{
public:
    Enemy(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();
};

#endif