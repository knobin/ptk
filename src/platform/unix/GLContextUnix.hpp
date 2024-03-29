//
//  platform/unix/GLContextUnix.hpp
//  pTK
//
//  Created by Robin Gustafsson on 2020-12-26.
//

#ifndef PTK_PLATFORM_UNIX_GLCONTEXT_HPP
#define PTK_PLATFORM_UNIX_GLCONTEXT_HPP

// Local Headers
#include "x11.hpp"

// pTK Headers
#include "ptk/core/ContextBase.hpp"

// OpenGL Headers
extern "C"
{
#define Status int
#include <GL/gl.h>
#include <GL/glx.h>
#undef Status
}

// Skia Headers
PTK_DISABLE_WARN_BEGIN()
// #include "include/gpu/GrContext.h"
#include "include/gpu/GrDirectContext.h"
#include "include/gpu/gl/GrGLInterface.h"
PTK_DISABLE_WARN_END()

namespace pTK::Platform
{
    /** GLContextUnix class implementation.

        Context for a hardware based OpenGL Unix backend.
        All drawings will be done using the GPU.
    */
    class PTK_API GLContextUnix : public ContextBase
    {
    public:
        /** Constructs GLContextUnix with xlib window and size.

            @param window   xlib window
            @param size     size of the context
            @return         initialized GLContextUnix with values
        */
        GLContextUnix(::Window window, const Size& size);

        /** Destructor for GLContextUnix.

        */
        virtual ~GLContextUnix();

        /** Function for resizing the context.

            @param size     new size
        */
        void resize(const Size& size) override;

        /** Function for retrieving the SkSurface of the context.

            @return    SkSurface property
        */
        sk_sp<SkSurface> surface() const override;

        /** Function for swapping the buffers

        */
        void swapBuffers() override;

    private:
        ::Window m_window;
        XVisualInfo* m_visual;
        GLXContext m_GLContext;
        sk_sp<SkSurface> m_surface;
        sk_sp<GrDirectContext> m_context;
        sk_sp<const GrGLInterface> m_backendContext;
        GrContextOptions m_GrContextOptions;
        SkSurfaceProps m_props;
    };
} // namespace pTK::Platform

#endif // PTK_PLATFORM_UNIX_GLCONTEXT_HPP
