//
//  core/WindowInfo.hpp
//  pTK
//
//  Created by Robin Gustafsson on 2020-12-31.
//

#ifndef PTK_CORE_WINDOWINFO_HPP
#define PTK_CORE_WINDOWINFO_HPP

// pTK Headers
#include "ptk/menu/MenuBar.hpp"
#include "ptk/util/Point.hpp"
#include "ptk/util/SizePolicy.hpp"

// C++ Headers
#include <cstdint>
#include <memory>

namespace pTK
{
    /** WindowInfo struct implementation

        Flags that can be passed to the window constructor.

        Current flags are:
            -   backend:            Specifies which backend to use.
            -   position:           Open window at position.
            -   visibility:         Specifies the visibility of the window on creation.
            -   menus:              Ref to Menu Bar.
            -   ignoreGlobalMenu:   Ignore Application::menuBar() (if set).
    */
    struct PTK_API WindowInfo
    {
        /** Backend enum class implementation

            Specifies which backend that should be used.
        */
        enum class Backend : uint8_t
        {
            Software = 1,
            Hardware

            // TODO: Implement the following OpenGL and Metal to specify which backend.
            // They should also be a "subset" of the Hardware enum.
            // If the user specifies "Hardware" it will select the "best" available backend.
        };

        enum class Visibility : uint8_t
        {
            Windowed = 0, // Default
            Hidden
            // For now only visible and hidden states are available.
            // TODO: Implement the following Minimized, Maximized and FullScreen.
        };

        Backend backend{Backend::Hardware};
        Point position{100, 100};
        Visibility visibility{Visibility::Hidden};
        std::shared_ptr<MenuBar> menus{nullptr};
        SizePolicy sizePolicy{SizePolicy::Policy::Expanding, SizePolicy::Policy::Expanding};
    };
} // namespace pTK

#endif // PTK_CORE_WINDOWINFO_HPP
