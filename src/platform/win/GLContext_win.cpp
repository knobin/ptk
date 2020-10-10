//
//  platform/win/WinRasterContext.cpp
//  pTK
//
//  Created by Robin Gustafsson on 2020-04-20.
//

// Local Headers
#include "GLContext_win.hpp"

// OpenGL Windows Headers
#include <GL/gl.h>

// Skia Headers
#ifdef PTK_COMPILER_GCC
#pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wpedantic"
#elif PTK_COMPILER_CLANG
#pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
#elif PTK_COMPILER_MSVC
#pragma warning( push, 0 )
#endif
#include "include/gpu/gl/GrGLInterface.h"
#include "src/gpu/gl/GrGLUtil.h"
#include "src/utils/win/SkWGL.h"
#ifdef PTK_COMPILER_GCC
#pragma GCC diagnostic pop
#elif PTK_COMPILER_CLANG
#pragma clang diagnostic pop
#elif PTK_COMPILER_MSVC
#pragma warning( pop )
#endif

namespace pTK
{
    GLContext_win::GLContext_win(HWND hwnd, const Size& size)
        : ContextBase(size), m_hwnd{hwnd}, m_hglrc{}, m_context{nullptr}, m_info{}, m_colorType{},
            m_props{SkSurfaceProps::kUseDeviceIndependentFonts_Flag, SkSurfaceProps::kLegacyFontHost_InitType}
    {
        HDC dc{GetDC(hwnd)};
        m_hglrc = SkCreateWGLContext(dc, 1, false, kGLPreferCompatibilityProfile_SkWGLContextRequest);
        PTK_ASSERT(m_hglrc, "Failed to create OpenGL handle!");

        if (wglMakeCurrent(dc, m_hglrc))
        {
            glClearStencil(0);
            glClearColor(0, 0, 0, 0);
            glStencilMask(0xFFFFFFFF);
            glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

            auto glInterface = GrGLMakeNativeInterface();
            PTK_ASSERT(glInterface, "Failed to create interface!");
            m_context.reset(GrContext::MakeGL(glInterface).release());

            GrGLint buffer;
            GR_GL_GetIntegerv(glInterface.get(), GR_GL_FRAMEBUFFER_BINDING, &buffer);
            GrGLFramebufferInfo info;
            info.fFBOID = (GrGLuint)buffer;
            m_info.fFormat = GL_RGBA8;
            m_colorType = kRGBA_8888_SkColorType;

            resize(size);
        }
#ifdef PTK_DEBUG
        else
        {
            PTK_ASSERT(false, "Failed the wglMakeCurrent function!");
        }
#endif
    }

    GLContext_win::~GLContext_win()
    {
        // Apparently, surface needs to be destroyed before context.
        // Otherwise, SkRefCount will give a nice assert.
        m_surface.reset();
        m_context.reset();

        PTK_INFO("Deconstructed GLContext_win");
    }

    void GLContext_win::resize(const Size& size)
    {
        glViewport(0, 0, size.width, size.height);

        GrBackendRenderTarget backendRenderTarget(size.width, size.height, 1, 8, m_info);

        SkSurface *surface{SkSurface::MakeFromBackendRenderTarget(m_context.get(), backendRenderTarget,
                kBottomLeft_GrSurfaceOrigin, m_colorType, nullptr, &m_props).release()};
        PTK_ASSERT(surface, "Failed to create surface!");
        m_surface.reset(surface);

        //clear(Color{0xFFFFFFFF});
        PTK_INFO("Constructed GLContext_win: {}x{}", size.width, size.height);
        setSize(size);
    }

    sk_sp<SkSurface> GLContext_win::surface() const
    {
        return m_surface;
    }

    void GLContext_win::swapBuffers()
    {
        HDC dc{GetDC(m_hwnd)};
        SwapBuffers(dc);
        ReleaseDC(m_hwnd, dc);
    }
}