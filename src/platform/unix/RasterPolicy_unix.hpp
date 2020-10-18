//
//  platform/unix/RasterPolicy_unix.hpp
//  pTK
//
//  Created by Robin Gustafsson on 2020-10-17.
//

#ifndef PTK_PlATFORM_UNIX_RASTERPOLICY_HPP
#define PTK_PlATFORM_UNIX_RASTERPOLICY_HPP

// Local Headers
#include "ptk/util/Size.hpp"

// Skia Headers
#include <include/core/SkImageInfo.h>

// X11 Headers
#include <X11/Xlib.h>
#include <X11/Xutil.h>

namespace pTK
{
    /** RasterPolicy_unix class implementation.

        This is a policy for the RasterContext class.
        It needs these public functions:
            - resize
            - swapBuffers
        and these public variables:
            - size
            - pixels
            - colorType
        For more information see the RasterContext header file.
    */
    class RasterPolicy_unix
    {
    public:
        /** Deleted constructor for RasterPolicy_unix

        */
        RasterPolicy_unix() = delete;

        /** Constructs RasterPolicy_unix with default values.

            @param hwnd   HWND
            @return       default initialized RasterPolicy_unix
        */
        RasterPolicy_unix(Display *display, ::Window window, XVisualInfo info);

        /** Deconstructor for RasterPolicy_unix.

        */
        ~RasterPolicy_unix();

        /** Function for resizing.

            @param nSize    new size
            @return         true if resized, otherwise false
        */
        bool resize(const Size& nSize);

        /** Function to swap the buffers after drawing.

        */
        void swapBuffers() const;

    public:
        std::size_t size{0};
        void *pixels{nullptr};
        const SkColorType colorType{kBGRA_8888_SkColorType};

    private:
        Display *m_display;
        ::Window m_window;
        XVisualInfo m_info;
        XImage* m_image;
        GC m_gc;
        Size wSize;
    };
}

#endif // PTK_PlATFORM_WIN_RASTERPOLICY_HPP