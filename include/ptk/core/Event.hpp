//
//  core/Event.hpp
//  pTK
//
//  Created by Robin Gustafsson on 2019-06-12.
//

#ifndef PTK_CORE_EVENT_HPP
#define PTK_CORE_EVENT_HPP

// pTK Headers
#include "ptk/core/Defines.hpp"

namespace pTK
{
    /** Event class implementation.

        This class is the base class for events.
        It specifies which event that occurred and cannot be
        created without specifying the category and type.

        Event::Category and Event::Type cannot be changed after the
        event is created.
    */
    class PTK_API Event
    {
    public:
        /** Event::Type enum class implementation.

            This enum class is to specify the event type of the event.
        */
        enum class Type
        {
            NONE = 0,
            WindowClose,
            WindowLostFocus,
            WindowFocus,
            WindowPaint,
            WindowResize,
            WindowMove,
            WindowMinimize,
            WindowRestore,
            WindowScale,
            KeyPressed,
            KeyReleased,
            KeyInput,
            MouseButtonPressed,
            MouseButtonReleased,
            MouseMoved,
            MouseScrolled
        };

        /** Event::Category enum class implementation.

            This enum class is to specify the category type of the event.
        */
        enum class Category
        {
            NONE = 0,
            Window,
            Keyboard,
            Mouse
        };

    public:
        /** Constructs Event with default values with t_category
            and t_type.

            @param t_category  category of event
            @param t_type      type of event
            @return            default initialized Event
        */
        constexpr Event(Category t_category, Type t_type) noexcept
            : category{t_category},
              type{t_type}
        {}

        /** Destructor for Event.

        */
        virtual ~Event() = default;

        // Category of the event.
        Category category;

        // Type of the event.
        Type type;
    };
} // namespace pTK

#endif // PTK_CORE_EVENT_HPP
