#pragma once

#include "feospch.h"

namespace FEOS::Event
{
    #define FEOS_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

    #define EVENT_CLASS_TYPE(type)                                                  \
            static EventType GetStaticType() { return EventType::type; }            \
            virtual EventType GetType() const override { return GetStaticType(); }  \
            virtual const char* GetName() const override { return #type; }

    #define EVENT_CLASS_CATEGORY(category) \
            virtual EventCategory GetCategory() const override { return category; }
    
    #define EVENT_TO_STRING(output)                 \
            std::string ToString() const override   \
            {                                       \
                std::stringstream ss;               \
                ss << output;                       \
                return ss.str();                    \
            }


    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowMinimize, WindowFocus, WindowLostFocus, WindowMoved,
        KeyPressed, KeyReleased, KeyType,
        MouseMoved, MouseScrolled, MouseButtonPressed, MouseButtonReleased,
        ChangePath, CopyFile, DeleteFile, MoveFile, AddFile
    };

    using EventCategory = uint16_t;
    enum EventCategoryEnum
    {
        NoneCategory =        0,
        ApplicationCategory = 1 << 0,
        InputCategory =       1 << 1,
        KeyboardCategory =    1 << 2,
        MouseCategory =       1 << 3,
        MouseButtonCategory = 1 << 4,
        FileSystemCategory =  1 << 5,
    };

    class Event
    {
    public:
        virtual ~Event() = default;

        virtual EventType GetType() const = 0;
        virtual const char* GetName() const = 0;
        virtual EventCategory GetCategory() const = 0;
        
        bool IsInCategory(EventCategory category) const
        {
            return GetCategory() & category;
        }

        virtual std::string ToString() const { return GetName(); }

    public:
        bool Handled = false;
    };

    class Dispatcher
    {
    public:
        Dispatcher(Event& e)
            : m_Event(e)
        { }

        template<typename T, typename F>
        bool Dispatch(const F& func)
        {
            if (m_Event.GetType() == T::GetStaticType())
            {
                m_Event.Handled |= func(static_cast<T&>(m_Event));
                return true;
            }
            return false;
        }
    
    private:
        Event& m_Event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }
}
