#pragma once

#include "FileExplorer/Events/Event.h"


namespace FEOS::Event
{
    class WindowClose : public Event
    {
    public:
        WindowClose() = default;

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(ApplicationCategory)
        
        EVENT_TO_STRING("WindowCloseEvent")
    };

    class WindowResize : public Event
    {
    public:
        WindowResize(uint32_t width, uint32_t height)
            : m_Width(width), m_Height(height)
        { }
    
        uint32_t GetWidth() const { return m_Width; }
        uint32_t GetHeight() const { return m_Height; }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(ApplicationCategory)

        EVENT_TO_STRING("WindowResizeEvent: " << m_Width << ", " << m_Height)

    private:
        uint32_t m_Width, m_Height;
    };

    class WindowMinimize : public Event
    {
    public:
        WindowMinimize() = default;

        EVENT_CLASS_TYPE(WindowMinimize)
        EVENT_CLASS_CATEGORY(ApplicationCategory)
    
        EVENT_TO_STRING("WindowMinimizeEvent")
    };
}