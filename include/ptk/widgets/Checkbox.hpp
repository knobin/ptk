//
//  widgets/Checkbox.hpp
//  pTK
//
//  Created by Robin Gustafsson on 2019-09-11.
//

#ifndef PTK_WIDGETS_CHECKBOX_HPP
#define PTK_WIDGETS_CHECKBOX_HPP

// Local Headers
#include "ptk/widgets/Rectangle.hpp"

namespace pTK
{
    /** Checkbox class implementation.
     
        This class implements a basic Checkbox.
        It includes all the necessary function for
        it to work.

        Checkbox specific functions implemented are:
            - bool status();
            - void set(bool status):
            - bool toggle();

        An extra callback is also present for overriding when
        the checkbox is toggled.
    */
    class Checkbox : public Rectangle
    {
    public:
        /** Checkbox Button with default values.
         
            @return    default initialized Checkbox
        */
        Checkbox();
        virtual ~Checkbox() = default;
        
        /** Draw function.
            Function is called when it is time to draw.
         
            Derived from Drawable.

            @param canvas  Canvas to draw to
        */
        void onDraw(SkCanvas* canvas) override;
        
        /** Function for retrieving the status.
         
            @return    status
        */
        bool status() const;

        /** Function for setting the status.
         
            @param status  he status toggled to.
        */
        void set(bool status);

        /** Function for toggling the status.
         
            @return    the status toggled to.
        */
        bool toggle();
        
        /** Function for handling when mouse is entering.
         
            Derived from EventFunctions.
        */
        bool onEnterEvent() override;
        
        /** Function for handling when mouse is leaving.
         
            Derived from EventFunctions.
        */
        bool onLeaveEvent() override;
        
        /** Function for handling when mouse is clicking.
         
            Derived from EventFunctions.
         
            @param button      which button on mouse triggered the event.
            @param position    x and y position
        */
        bool onClickEvent(Mouse::Button, const Point&) override;
        
        /** Function for handling when mouse is released.
         
            Derived from EventFunctions.
         
            @param button      which button on mouse triggered the event.
            @param position    x and y position
        */
        bool onReleaseEvent(Mouse::Button, const Point&) override;
        
        /** Function for handling when the checkbox is toggled.
         
            @param status    status on toggle.
        */
        virtual void onToggleEvent(bool status);
        
        /** Function for handling when the checkbox is toggled.
         
            @param callback    function to call on toggle.
        */
        void onToggle(const std::function<bool(bool status)>& callback);
        
    private:
        bool m_checked = false;
        bool m_hover = false;
        bool m_click = false;
        byte m_state = 0;
        Color m_checkColor;
        std::function<bool(bool status)> m_toggleCallback;
        
        void drawChecked(SkCanvas* canvas);
        void drawStates(SkCanvas* canvas);
        
        void internalToggle();
    };
    
}

#endif // PTK_WIDGETS_CHECKBOX_HPP
