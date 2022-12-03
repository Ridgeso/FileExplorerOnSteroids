#pragma once

#include "FileExplorer/Events/Event.h"
#include "FileExplorer/Core/KeyCodes.h"


namespace FEOS::Event
{
    class MouseMoved : public Event
    {
    public:
        MouseMoved(const float x, const float y)
            : m_MouseX(x), m_MouseY(y)
        { }

        float GetX() const { return m_MouseX; }
        float GetY() const { return m_MouseY; }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(MouseCategory | InputCategory)

        EVENT_TO_STRING("MouseMoveEvent: " << m_MouseX << ", " << m_MouseY)

    private:
        float m_MouseX, m_MouseY;
    };

    class MouseScrolled : public Event
    {
    public:
        MouseScrolled(const float xOffset, const float yOffset)
            : m_xOffset(xOffset), m_yOffset(yOffset)
        { }

        float GetXOffset() const { return m_xOffset; }
        float GetYOffset() const { return m_yOffset; }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(MouseCategory | InputCategory)

        EVENT_TO_STRING("MouseScrolledEvent: " << m_xOffset << ", " << m_yOffset)
    
    private:
        float m_xOffset, m_yOffset;
    };

    class MouseButton : public Event
    {
    public:
        KeyCodes::KeyCode GetMouseButton() const { return m_Button; }

        EVENT_CLASS_CATEGORY(MouseCategory | InputCategory | MouseButtonCategory)

    protected:
        MouseButton(const KeyCodes::KeyCode button)
            : m_Button(button)
        { }

        KeyCodes::KeyCode m_Button;
    };

    class MouseButtonPressed : public MouseButton
    {
    public:
        MouseButtonPressed(const KeyCodes::KeyCode button)
            : MouseButton(button)
        { }

        EVENT_CLASS_TYPE(MouseButtonPressed)

        EVENT_TO_STRING("MouseButtonPressed: " << m_Button)
    };

    class MouseButtonReleased : public MouseButton
    {
    public:
        MouseButtonReleased(const KeyCodes::KeyCode button)
            : MouseButton(button)
        { }

        EVENT_CLASS_TYPE(MouseButtonReleased)

        EVENT_TO_STRING("MouseButtonReleased: " << m_Button)
    };
}
