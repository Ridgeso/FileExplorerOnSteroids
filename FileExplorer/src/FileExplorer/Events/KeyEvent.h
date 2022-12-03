#pragma once

#include "FileExplorer/Events/Event.h"
#include "FileExplorer/Core/KeyCodes.h"


namespace FEOS::Event
{
    class KeyEvent : public Event
    {
    public:
        KeyCodes::KeyCode GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(InputCategory | KeyboardCategory)

    protected:
        KeyEvent(const KeyCodes::KeyCode keycode)
            : m_KeyCode(keycode) {}

        KeyCodes::KeyCode m_KeyCode;
    };

    class KeyPressed : public KeyEvent
    {
    public:
        KeyPressed(const KeyCodes::KeyCode keycode, bool isRepeat = false)
            : KeyEvent(keycode), m_IsRepeat(isRepeat)
        { }

        bool IsRepeat() const { return m_IsRepeat; }

        EVENT_CLASS_TYPE(KeyPressed)

        EVENT_TO_STRING("KeyPressedEvent: " << m_KeyCode << " (repeat = " << m_IsRepeat << ")")

    private:
        bool m_IsRepeat;
    };

    class KeyReleased : public KeyEvent
    {
    public:
        KeyReleased(const KeyCodes::KeyCode keycode)
            : KeyEvent(keycode)
        {}

        EVENT_CLASS_TYPE(KeyReleased)

        EVENT_TO_STRING("KeyReleasedEvent: " << m_KeyCode)
    };

    class KeyType : public KeyEvent
    {
    public:
        KeyType(const KeyCodes::KeyCode keycode)
            : KeyEvent(keycode) {}

        EVENT_CLASS_TYPE(KeyType)

        EVENT_TO_STRING("KeyTypedEvent: " << m_KeyCode)
    };
}