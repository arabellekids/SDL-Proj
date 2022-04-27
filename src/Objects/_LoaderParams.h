#ifndef __LOADERPARAMS__
#define __LOADERPARAMS__

#include <string>

class LoaderParams
{
public:
    LoaderParams(int x,int y, int w,int h, std::string texID) : m_x(x),m_y(y), m_w(w),m_h(h), m_texID(texID)
    {
    }
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    int getW() const { return m_w; }
    int getH() const { return m_h; }

    std::string getTexID() const { return m_texID; }
private:
    int m_x;
    int m_y;
    
    int m_w;
    int m_h;
    
    std::string m_texID;
};

#endif