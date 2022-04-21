#ifndef __GAMEOBJECT__
#define __GAMEOBJECT__

#include <string>
#include <SDL2/SDL.h>

class GameObject
{
public:
    GameObject(){}

    virtual void load(int x,int y, int width,int height, std::string texID);

    virtual void draw(SDL_Renderer* pRenderer);
    virtual void update();
    virtual void clean() {}

protected:
    std::string m_texID;

    int m_curFrame;
    int m_curRow;

    int m_x;
    int m_y;

    int m_width;
    int m_height;
};

#endif