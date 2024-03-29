//
//  core/Defines.hpp
//  pTK
//
//  Created by Robin Gustafsson on 2021-01-21.
//

// clang-format off

#ifndef PTK_CORE_DEFINES_HPP
#define PTK_CORE_DEFINES_HPP

// Build type.
#if !defined(PTK_DEBUG) && !defined(PTK_RELEASE)
    #ifdef NDEBUG
        #define PTK_RELEASE
    #else
        #define PTK_DEBUG
    #endif
#endif

// Enable debug options.
#if defined(PTK_DEBUG)
    #if !defined(PTK_ENABLE_ASSERT)
        #define PTK_ENABLE_ASSERT
    #endif
#endif

// Check platform.
#if !defined(PTK_PLATFORM_WINDOWS) && !defined(PTK_PLATFORM_APPLE) && !defined(PTK_PLATFORM_UNIX)
    #if defined(_WIN32)
        #define PTK_PLATFORM_WINDOWS
    #elif defined(__APPLE__)
        #include "TargetConditionals.h"
        #if TARGET_OS_MAC
            #define PTK_PLATFORM_APPLE
        #else
            #error "Unsupported Apple Target!"
        #endif
    #elif defined(__unix__)
        #define PTK_PLATFORM_UNIX
    #else
        #if !defined(PTK_SUPPRESS_PLATFORM_ERROR)
            #error "Unsupported platform!"
        #endif
    #endif
#endif

// Check compiler.
#if !defined(PTK_COMPILER_CLANG) && !defined(PTK_COMPILER_GCC) && !defined(PTK_COMPILER_MSVC)
    #if defined(__clang__)
        #define PTK_COMPILER_CLANG
    #elif defined(__GNUC__)
        #define PTK_COMPILER_GCC
    #elif defined(_MSC_VER)
        #define PTK_COMPILER_MSVC
    #else
        #warning "Unknown compiler!"
    #endif
#endif

// Shared library defines.
#if !defined(PTK_API)
    #if defined(PTK_SHARED)
        #if defined(PTK_COMPILER_MSVC)
            #if defined(PTK_EXPORTS)
                #define PTK_API __declspec(dllexport)
            #else
                #define PTK_API __declspec(dllimport)
            #endif
        #else
            #define PTK_API __attribute__((visibility("default")))
        #endif
    #else
        #define PTK_API
    #endif
#endif

// Unused parameter.
#if defined(PTK_COMPILER_GCC)
    #define UNUSED(x) x __attribute__((unused))
#elif defined(PTK_COMPILER_CLANG)
    #define UNUSED(x) x __attribute__((unused))
#elif defined(PTK_COMPILER_MSVC)
    #define UNUSED(x) __pragma(warning(suppress:4100)) x
#else
    #define UNUSED(x)
#endif

// Ignore all warnings (Begin)
#if !defined(PTK_DISABLE_WARN_BEGIN)
    #if defined(PTK_COMPILER_GCC)
        // TODO
        #define PTK_DISABLE_WARN_BEGIN()
    #elif defined(PTK_COMPILER_CLANG)
        #define PTK_DISABLE_WARN_BEGIN() \
            _Pragma("clang diagnostic push") \
            _Pragma("clang diagnostic ignored \"-Weverything\"")
    #elif defined(PTK_COMPILER_MSVC)
        #define PTK_DISABLE_WARN_BEGIN() __pragma(warning(push, 0))
    #else
        #define PTK_DISABLE_WARN_BEGIN()
    #endif
#endif

// Ignore all warnings (End)
#if !defined(PTK_DISABLE_WARN_END)
    #if defined(PTK_COMPILER_GCC)
        // TODO
        #define PTK_DISABLE_WARN_END()
    #elif defined(PTK_COMPILER_CLANG)
        #define PTK_DISABLE_WARN_END() _Pragma("clang diagnostic pop");
    #elif defined(PTK_COMPILER_MSVC)
        #define PTK_DISABLE_WARN_END() __pragma(warning(pop))
    #else
        #define PTK_DISABLE_WARN_END()
    #endif
#endif

#endif // PTK_CORE_DEFINES_HPP

// clang-format on
