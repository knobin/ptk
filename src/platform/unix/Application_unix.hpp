//
//  platform/win/Platform_unix.hpp
//  pTK
//
//  Created by Robin Gustafsson on 2020-10-10.
//

#ifndef PTK_PLATFORM_UNIX_APPLICATION_HPP
#define PTK_PLATFORM_UNIX_APPLICATION_HPP

// Local Headers
#include "ptk/core/platform/ApplicationBase.hpp"

// X11 Heades
#include <X11/Xlib.h>

namespace pTK
{
    /** Application_unix class implementation.

        Base application implementation for Unix.
        This class will be instantiated when the Application is created.
    */
    class Application_unix : public ApplicationBase
    {
    public:
        /** Constructs Application_unix with default values.

            @return        default initialized Application_unix
        */
        Application_unix();

        /** Deconstructor for Application_unix

        */
        virtual ~Application_unix();

        int messageLoop() override;

        /** Function for closing the application should close.

        */
        void close() override;

        static Display *getDisplay();

    private:
        bool init();
    };
}

#endif // PTK_PLATFORM_UNIX_APPLICATION_HPP