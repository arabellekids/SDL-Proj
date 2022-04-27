#include "_Objects.h"
#include "../Input/InputHandler.h"
#include "../Math/Vector2D.h"

MenuButton::MenuButton(const LoaderParams* pParams, void (*callback) ()) : \
SDLGameObject(pParams), m_callback(callback)
{
    m_curFrame = MOUSE_OUT; // Start at frame 0
}
void MenuButton::draw()
{
    SDLGameObject::draw(); // Use the base class drawing
}
void MenuButton::update()
{
    auto& pMousePos = InputHandler::Instance()->getMousePos();

    // Is mouse inside button rect?
    if(pMousePos.getX() < (m_pos.getX() + m_w)
    && pMousePos.getX() > m_pos.getX()
    && pMousePos.getY() < (m_pos.getY() + m_h)
    && pMousePos.getY() > m_pos.getY())
    {
        // Mouse clicked on button
        if(InputHandler::Instance()->getMouseButton(MOUSE_LEFT) && m_bReleased)
        {
            m_curFrame = MOUSE_CLICKED;

            m_callback(); // Call the callback function
            m_bReleased = false;
        }
        else if(!InputHandler::Instance()->getMouseButton(MOUSE_LEFT))
        {
            m_bReleased = true;
            m_curFrame = MOUSE_OVER;
        }
    }
    // Mouse outside button
    else
    {
        m_curFrame = MOUSE_OUT;
    }
}
void MenuButton::clean()
{
    SDLGameObject::clean();
}