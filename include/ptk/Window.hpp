//
//  Window.hpp
//  pTK
//
//  Created by Robin Gustafsson on 2019-06-12.
//

#ifndef PTK_WINDOW_HPP
#define PTK_WINDOW_HPP

// Local Headers
#include "ptk/core/Canvas.hpp"
#include "ptk/core/Event.hpp"
#include "ptk/core/Container.hpp"
#include "ptk/util/Vec2.hpp"

// C++ Headers
#include <string>
#include <queue>

// GLEW Headers
//#include <GL/glew.h>

// GLFW Headers
#include <GLFW/glfw3.h>

namespace pTK
{
    struct WindowData
    {
        std::string name;
        Vec2<uint32_t> size;
        Vec2<float> scale;
    };

    class Window : public Container
    {
    public:
        Window(const std::string& name, unsigned int width, unsigned int height);
        virtual ~Window();

        void pollEvents();
        void swapBuffers();
        bool shouldClose();
        void resize(unsigned int width, unsigned int height);
        
        // Visible
        void show();
        void hide();
        
        // Event
        void sendEvent(Event* event);
        void handleEvents();
        
    private:
        // Window
        GLFWwindow* m_window;
        WindowData m_data;
        Canvas* m_mainCanvas;
        Canvas* m_drawCanvas;
        std::queue<Event*> m_events;

        // Init Functions
        void initGLFW();
        
        // Set Event Callbacks
        void setWindowCallbacks();
        void setMouseCallbacks();
        void setKeyCallbacks();
        
        // Event processing
        void handleKeyEvent(Event* event);
        void handleMouseEvent(Event* event);
        void handleWindowEvent(Event* event);
        
        void draw();
    };
}

#endif // PTK_WINDOW_HPP