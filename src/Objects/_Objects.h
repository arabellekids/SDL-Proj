#ifndef __OBJECTS__
#define __OBJECTS__

#include "_LoaderParams.h"

// The base Gameobject class
class GameObject
{
public:
    virtual void draw()=0;
    virtual void update()=0;
    virtual void clean()=0;

protected:
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
    int m_x;
    int m_y;
    
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