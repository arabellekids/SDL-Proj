#ifndef __LOADERPARAMS__
#define __LOADERPARAMS__

#include <string>

class LoaderParams
{
public:
    LoaderParams(int x,int y, int w,int h, int numFrames,
    std::string texID, int animSpeed=0, int callbackID=0) :
    m_x(x),m_y(y), m_w(w),m_h(h), m_numFrames(numFrames),
    m_texID(texID), m_animSpeed(animSpeed), m_callbackID(callbackID)
    {
    }
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    int getW() const { return m_w; }
    int getH() const { return m_h; }
    int getNumFrames() const { return m_numFrames; }
    int getAnimSpeed() const { return m_animSpeed; }
    int getCallbackID() const { return m_callbackID; }
    
    std::string getTexID() const { return m_texID; }
private:
    int m_x;
    int m_y;
    
    int m_w;
    int m_h;

    int m_numFrames;

    std::string m_texID;
    
    int m_animSpeed;
    
    int m_callbackID;
    
    
};

#endif