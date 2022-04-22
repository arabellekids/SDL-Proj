#ifndef __VECTOR2D__
#define __VECTOR2D__

#include <math.h>

class Vector2D
{
public:
    Vector2D() {}
    Vector2D(float x, float y) : m_x(x), m_y(y) {}

    float length() { return sqrtf(m_x*m_x + m_y*m_y); }
    void normalize()
    {
        float l = length();
        // Vector where x==0 and y==0
        if (l <= 0) { return; }

        (*this) *= (1 / l);
    }

    float getX() { return m_x; }
    float getY() { return m_y; }

    void setX(float x) { m_x = x; }
    void setY(float y) { m_y = y; }

    // Addition
    Vector2D operator+ (const Vector2D& v2) const
    {
        return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
    }
    friend Vector2D& operator+= (Vector2D& v1, const Vector2D& v2)
    {
        v1.m_x += v2.m_x;
        v1.m_y += v2.m_y;

        return v1;
    }
    // Subtraction
    Vector2D operator- (const Vector2D& v2) const
    {
        return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
    }
    friend Vector2D& operator-= (Vector2D& v1, const Vector2D& v2)
    {
        v1.m_x -= v2.m_x;
        v1.m_y -= v2.m_y;

        return v1;
    }
    
    // Multiplication
    Vector2D operator* (float scaler)
    {
        return Vector2D(m_x * scaler, m_y * scaler);
    }
    Vector2D& operator*= (float scaler)
    {
        m_x *= scaler;
        m_y *= scaler;

        return *this;
    }
    // Division
    Vector2D operator/ (float scaler)
    {
        return Vector2D(m_x / scaler, m_y / scaler);
    }
    Vector2D& operator/= (float scaler)
    {
        m_x /= scaler;
        m_y /= scaler;

        return *this;
    }

private:
    float m_x;
    float m_y;
};

#endif