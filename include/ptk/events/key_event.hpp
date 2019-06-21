//
//  events/keyevent.hpp
//  pTK
//
//  Created by Robin Gustafsson on 2019-06-12.
//

#ifndef PTK_EVENTS_KEYEVENT_HPP
#define PTK_EVENTS_KEYEVENT_HPP

// Local Headers
#include "ptk/core/event.hpp"

// C++ Headers
#include <cstdint>

namespace pTK
{
    /** KeyEvent class implementation.
     
     Derived from Event, this class if for creating
     events from the keyboard. Such as Key presses or
     releases.
     */
    class KeyEvent : public Event
    {
    public:
        /** Constructs KeyEvent with default values with t_type and t_keycode.
         
         @param type        press or release
         @param keycode     associated keycode
         @return            default initialized KeyEvent
         */
        KeyEvent(EventType type, int32_t keycode)
            : Event(EventCategory::Key, type), m_keycode{keycode}
        {
        }
        ~KeyEvent() final = default;

        /** Function for retrieving the associated keycode.
         
         @return    Pressed or Released keycode
         */
        int32_t get_keycode() const { return m_keycode; }

    private:
        int32_t m_keycode;
    };
}

#endif // PTK_EVENTS_KEYEVENT_HPP
