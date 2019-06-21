//
//  core/event_handlers.hpp
//  pTK
//
//  Created by Robin Gustafsson on 2019-06-21.
//

#ifndef PTK_CORE_EVENT_FUNCTIONS_HPP
#define PTK_CORE_EVENT_FUNCTIONS_HPP

namespace pTK
{
    /** EventFunctions class implementation.
     
     This class is to handle the incoming events.
     
     Depending on the event category and type, one of
     the defined functions below will be called.
     */
    class EventFunctions
    {
    public:
        EventFunctions() = default;
        virtual ~EventFunctions() = default;
        
        /** Function for handling when a key is pressed or released.
         
         @param type    Key event (press or release)
         @param int     Keycode
         */
        virtual void on_key_event(EventType, int) {}
        
        /** Function for handling when mouse is entering.
         
         */
        virtual void on_hover_event() {}
        
        /** Function for handling when mouse is leaving.
         
         */
        virtual void on_leave_event() {}
        
        /** Function for handling when mouse is scrolling.
         
         @param offset     x and y offset
         */
        virtual void on_scroll_event(const Vec2<int>&) {}
        
        /** Function for handling when mouse is clicking.
         
         @param button      which button on mouse triggered the event.
         @param position    x and y position
         */
        virtual void on_click_event(MouseButton, const Vec2<int>&) {}
        
        /** Function for handling when mouse is released.
         
         @param button      which button on mouse triggered the event.
         @param position    x and y position
         */
        virtual void on_release_event(MouseButton, const Vec2<int>&) {}
    };
}

#endif // PTK_CORE_EVENT_FUNCTIONS_HPP

