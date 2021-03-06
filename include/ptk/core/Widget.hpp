//
//  core/Widget.hpp
//  pTK
//
//  Created by Robin Gustafsson on 2019-06-19.
//

#ifndef PTK_CORE_WIDGET_HPP
#define PTK_CORE_WIDGET_HPP

// Local Headers
#include "ptk/core/Drawable.hpp"
#include "ptk/core/EventHandling.hpp"
#include "ptk/core/Sizable.hpp"
#include "ptk/util/Point.hpp"
#include "ptk/util/Alignment.hpp"

// C++ Headers
#include <string>

namespace pTK
{
    /** Widget class implementation.
     
        This class is low level class for widget, that
        has the essential component for rendering.
    */
    class Widget : public Alignment, public Drawable, public EventHandling, public Sizable
    {
    public:
        /** Constructs Widget with default values.
         
            @return    default initialized Widget
        */
        Widget();

        /** Deconstructor for Widget.
        
        */
        virtual ~Widget() = default;
        
        /** Function sets the Container parent of the Widget.
         
            @param parent  the parent Container
        */
        void setParent(Widget* parent);
        
        /** Function for retrieving the Container parent of the Widget.
         
            @return  the Container parent of the Widget
        */
        Widget* getParent() const;
        
        /** Function for requesting the position of the Widget.
         
            @param pos  requested position of the Widget.
        */
        virtual void setPosHint(const Point& pos);
        
        /** Function for retrieving the current position of the Widget.
         
            @return  current position
        */
        const Point& getPosition() const;
        
        /** Function for setting the name of the Widget.
         
            @param  name   name of the widget
        */
        void setName(const std::string& name);
        
        /** Function for retrieving the name of the Widget.
         
            @return  name
        */
        const std::string& getName() const;

        /** Function for notifying the parent of a change and
            to put it on an internal render queue.
        */
        bool update();

        /** Function for notifying the parent of a change and
            put it on an internal render queue.
        */
        bool draw();
        
    protected:
        /** Function for updating the child.
         
            override this function for receiving update
            requests from children (update function is called
            in the child). i.e. something in the
            child has changed, probably a new size or 
            position is set.

            @param child    request from

        */
        virtual bool updateChild(Widget*);
        
        /** Function for redrawing the child.

            override this function for receiving draw
            requests from children (draw function is called
            in the child). i.e. something in the
            child has changed and it only needs to be 
            redrawn.
         
            @param child    request from
        */
        virtual bool drawChild(Widget*);

    private:
        // Size functions derived from Sizable.
        void onResize(const Size& size) override;
        void onLimitChange(const Size& min, const Size& max) override;

        // Alignment functions derived from Alignment.
        void onAlignChange(std::underlying_type<Align>::type) override;
        void onMarginChange(const Margin&) override;
        void onPaddingChange(const Padding&) override;

    private:
        Widget* m_parent;
        Point m_pos;
        std::string m_name;
    };
    
    // Comparison operators.
    bool operator==(const Widget& lhs, const Widget& rhs);
    bool operator!=(const Widget& lhs, const Widget& rhs);
}

#endif // PTK_CORE_WIDGET_HPP

