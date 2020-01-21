//
//  Window.cpp
//  pTK
//
//  Created by Robin Gustafsson on 2019-06-12.
//

// Local Headers
#include "ptk/Window.hpp"
#include "ptk/events/KeyEvent.hpp"
#include "ptk/events/MouseEvent.hpp"
#include "ptk/events/WindowEvent.hpp"
#include "ptk/util/Semaphore.hpp"
#include "ptk/Core.hpp"

// C++ Headers
#include <exception>

namespace pTK
{
    Window::Window(const std::string& name, uint width, uint height)
        : VBox(), Singleton(),
            m_window{nullptr}, m_scale{1.0f, 1.0f},
            m_drawCanvas{nullptr}, m_eventQueue{}, m_draw{false}
    {
        // Set Widget properties.
        Sizable::setSize({static_cast<int>(width), static_cast<int>(height)});
        setName(name);
        
        initGLFW();

        // Create Window.
        m_window = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), name.c_str(), nullptr, nullptr);
        PTK_ASSERT(m_window, "Failed to create GLFW Window");
        PTK_INFO("GLFW Window Created, {0:d}x{1:d}", static_cast<int>(width), static_cast<int>(height));
        
        // Get Monitor Scale
        glfwGetWindowContentScale(m_window, &m_scale.x, &m_scale.y);
        PTK_INFO("Monitor scale, {0:0.2f}x{1:0.2f}", m_scale.x, m_scale.y);
        
        // Bind context.
        glfwMakeContextCurrent(m_window);
        
        // Init Canvas
        Size wSize = getContentSize();
        m_drawCanvas = std::make_unique<Canvas>(Size(wSize.width, wSize.height));
        PTK_ASSERT(m_drawCanvas, "Failed to create Canvas");
        
        // Set Callbacks
        glfwSetWindowUserPointer(m_window, this);
        setWindowCallbacks();
        setMouseCallbacks();
        setKeyCallbacks();
        
        PTK_INFO("Window Initialization finished");
    }
    
    // Init Functions
    void Window::initGLFW()
    {
        // Initialize and configure of GLFW.
        glfwInit();
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE); // Hide window on creation.
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_STENCIL_BITS, 8);
        glfwWindowHint(GLFW_DEPTH_BITS, 0);
		glfwWindowHint(GLFW_SAMPLES, 4);
    }
    
    // Set Event Callbacks
    void Window::setWindowCallbacks()
    {
        // void window_size_callback(GLFWwindow* window, int width, int height)
        glfwSetWindowSizeCallback(m_window, [](GLFWwindow* t_window, int t_width, int t_height){
            auto window = static_cast<Window*>(glfwGetWindowUserPointer(t_window));
            window->sendEvent<ResizeEvent>(Size{t_width, t_height}, window->getContentSize());
            window->handleEvents();
        });
        
        // void window_close_callback(GLFWwindow* window)
        glfwSetWindowCloseCallback(m_window, [](GLFWwindow* t_window){
            auto window = static_cast<Window*>(glfwGetWindowUserPointer(t_window));
            window->sendEvent<Event>(Event::Category::Window, Event::Type::WindowClose);
        });

        // void window_maximize_callback(GLFWwindow* window, int maximized)
        glfwSetWindowMaximizeCallback(m_window, [](GLFWwindow* t_window, int){
            // TODO: Should create a resize EventFunction. 
            auto window = static_cast<Window*>(glfwGetWindowUserPointer(t_window));
            int width, height;
            glfwGetWindowSize(t_window, &width, &height);
            window->sendEvent<ResizeEvent>(Size{width, height}, window->getContentSize());
        });
    }
    
    void Window::setMouseCallbacks()
    {
        // void cursor_enter_callback(GLFWwindow* window, int entered)
        glfwSetCursorEnterCallback(m_window,[](GLFWwindow* t_window, int entered){
            if (!entered)
            {
                auto window = static_cast<Window*>(glfwGetWindowUserPointer(t_window));
                window->sendEvent<MotionEvent>(-1, -1);
            }
        });
        
        // void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
        glfwSetCursorPosCallback(m_window, [](GLFWwindow* t_window, double t_xpos, double t_ypos){
            auto window = static_cast<Window*>(glfwGetWindowUserPointer(t_window));
            Size wSize = window->getSize();
            
            if ((t_xpos >= 0) && (t_xpos <= (wSize.width)))
                if ((t_ypos >= 0) && (t_ypos <= (wSize.height)))
                    window->sendEvent<MotionEvent>((int)t_xpos, (int)t_ypos);
        });
        // void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
        glfwSetMouseButtonCallback(m_window, [](GLFWwindow* t_window, int t_button, int t_action, int){
            auto window = static_cast<Window*>(glfwGetWindowUserPointer(t_window));
            
            double xpos, ypos;
            glfwGetCursorPos(t_window, &xpos, &ypos);
            
            Mouse::Button button;
            if (t_button == GLFW_MOUSE_BUTTON_LEFT)
                button = Mouse::Button::Left;
            else if (t_button == GLFW_MOUSE_BUTTON_MIDDLE)
                button = Mouse::Button::Middle;
            else if (t_button == GLFW_MOUSE_BUTTON_RIGHT)
                button = Mouse::Button::Right;
            else
                button = Mouse::Button::NONE;
            
            if (t_action == GLFW_PRESS)
                window->sendEvent<ButtonEvent>(Event::Type::MouseButtonPressed, button, xpos, ypos);
            else if (t_action == GLFW_RELEASE)
                window->sendEvent<ButtonEvent>(Event::Type::MouseButtonReleased, button, xpos, ypos);
        });
    }
    
    void Window::setKeyCallbacks()
    {
        // void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        glfwSetKeyCallback(m_window, [](GLFWwindow* t_window, int t_key, int, int t_action, int){
            auto window = static_cast<Window*>(glfwGetWindowUserPointer(t_window));
            if (t_action == GLFW_PRESS)
                window->sendEvent<KeyEvent>(Event::Type::KeyPressed, t_key);
            else if (t_action == GLFW_RELEASE)
                window->sendEvent<KeyEvent>(Event::Type::KeyReleased, t_key);
        });
    }

    Window::~Window()
    {
		// Free canvas before glfw to avoid OpenGL errors.
		m_drawCanvas.reset(nullptr);
        glfwDestroyWindow(m_window);
		glfwTerminate();
        PTK_INFO("Window Destroyed");
    }
    
    // Will be called when all children will need to redraw.
    // For example, window.show();
    void Window::forceDrawAll()
    {
        SkCanvas* canvas = m_drawCanvas->skCanvas();
        
        Color color = getBackground();
        m_drawCanvas->clear(color);
        
        // Apply monitor scale.
        SkMatrix matrix;
        matrix.setScale(m_scale.x, m_scale.y);
        canvas->setMatrix(matrix);
        
        for (iterator it = begin(); it != end(); it++)
            (*it)->onDraw(canvas);
        
        canvas->flush();
        swapBuffers();
    }
    
    void Window::onChildDraw(size_type)
    {
        sendEvent<Event>(Event::Category::Window, Event::Type::WindowDraw);
    }
    
    void Window::pollEvents()
    {
        glfwWaitEvents();
    }
    
    void Window::handleEvents()
    {
        size_t eventCount = m_eventQueue.size();
        for (uint i = 0; i < eventCount; i++)
        {
            Ref<Event> event = m_eventQueue.front();
            m_eventQueue.pop();
            
            if (event->category() == Event::Category::Window)
                handleWindowEvent(event.get());
            else if (event->category() == Event::Category::Key)
                handleKeyboardEvent(event.get());
            else if (event->category() == Event::Category::Mouse)
                handleMouseEvent(event.get());
#ifdef PTK_DEBUG
            else
                PTK_WARN("Unknown event");
#endif
        }
        
        // Quick fix when previous event cause a draw event.
        if (m_eventQueue.size() > 0)
        {
            Ref<Event> event = m_eventQueue.front();
            if (event->category() == Event::Category::Window)
            {
                handleWindowEvent(event.get());
                m_eventQueue.pop();
            }
        }

        if (m_draw)
        {
            forceDrawAll();
            m_draw = false;
        }
    }

    void Window::swapBuffers()
    {
        glfwSwapBuffers(m_window);
    }
    
    // Size
    Size Window::getContentSize() const
    {
        int width, height;
        glfwGetFramebufferSize(m_window, &width, &height);
        
        return Size(width, height);
    }
    
    const Vec2f& Window::getDPIScale() const
    {
        return m_scale;
    }
    
    void Window::setSize(const Size& size)
    {
        glfwSetWindowSize(m_window, size.width, size.height);
        Widget::setSize(size);
    }
    
    void Window::setMinSize(const Size& size)
    {
        Size wSize = getSize();
        Size contentMinSize = VBox::getMinSize();
        Size newMinSize;
        
        if (size.width != GLFW_DONT_CARE)
            newMinSize.width = ((size.width > contentMinSize.width) && (size.width <= wSize.width)) ? size.width : contentMinSize.width;
        else
            newMinSize.width = contentMinSize.width;
        
        if (size.height != GLFW_DONT_CARE)
            newMinSize.height = ((size.height > contentMinSize.height) && (size.height <= wSize.height)) ? size.height : contentMinSize.height;
        else
            newMinSize.height = contentMinSize.height;
        
        Sizable::setMinSize(newMinSize);
        setLimits(newMinSize, getMaxSize());
    }
    
    void Window::setMaxSize(const Size& size)
    {
        Size wSize = getSize();
        Size newMaxSize;
        
        newMaxSize.width = ((size.height >= wSize.height) && (size.height <= Size::Limits::Max)) ? size.width : Size::Limits::Max;
        newMaxSize.height = ((size.width >= wSize.width) && (size.width <= Size::Limits::Max)) ? size.width : Size::Limits::Max;
        
        Sizable::setMaxSize(newMaxSize);
        setLimits(getMinSize(), newMaxSize);
    }
    
    void Window::setLimits(const Size& minSize, const Size& maxSize)
    {
		int width = (maxSize.width == Size::Limits::Max) ? GLFW_DONT_CARE : maxSize.width;
		int height = (maxSize.height == Size::Limits::Max) ? GLFW_DONT_CARE : maxSize.height;
		glfwSetWindowSizeLimits(m_window, static_cast<int>(minSize.width), static_cast<int>(minSize.height), width, height);
    }

    // Close
    bool Window::shouldClose()
    {
        return (bool)glfwWindowShouldClose(m_window);
    }
    
    void Window::close()
    {
        glfwSetWindowShouldClose(m_window, GLFW_TRUE);
        sendEvent<Event>(Event::Category::Window, Event::Type::WindowClose);
    }
    
    // Visible
    void Window::show()
    {
        glfwShowWindow(m_window);
        forceDrawAll();
    }
    
    void Window::hide()
    {
        glfwHideWindow(m_window);
    }

    // Called by event thread.
    void Window::handleKeyboardEvent(Event* event)
    {
        PTK_ASSERT(event, "Undefined Event");
        KeyEvent* kEvent = static_cast<KeyEvent*>(event);
        handleKeyEvent(kEvent->type(), kEvent->get_keycode());
    }

    // Called by event thread.
    void Window::handleMouseEvent(Event* event)
    {
        PTK_ASSERT(event, "Undefined Event");
        Event::Type type = event->type();
        if (type == Event::Type::MouseMoved)
        {
            MotionEvent* mEvent = static_cast<MotionEvent*>(event);
            handleHoverEvent(mEvent->getPos());
        } else if (type == Event::Type::MouseButtonPressed || type == Event::Type::MouseButtonReleased)
        {
            ButtonEvent* bEvent = static_cast<ButtonEvent*>(event);
            Point pos{bEvent->getPos()};
            Mouse::Button btn = bEvent->getButton();
            if (type == Event::Type::MouseButtonPressed)
                handleClickEvent(btn, pos);
            else if (type == Event::Type::MouseButtonReleased)
                handleReleaseEvent(btn, pos);
        }
    }

    // Called by event thread.
    void Window::handleWindowEvent(Event* event)
    {
        PTK_ASSERT(event, "Undefined Event");
        Event::Type type = event->type();
        if (type == Event::Type::WindowDraw)
        {
            m_draw = true;
        }
        else if (type == Event::Type::WindowResize)
        {
            ResizeEvent* rEvent = (ResizeEvent*)event;
			Size cSize = rEvent->getContentSize();
            
            // Set Framebuffer Size.
            if (cSize != m_drawCanvas->getSize())
                m_drawCanvas->resize(cSize);
            
            // TODO: May conflict with eventThread.
            Size contentMinSize = VBox::getMinSize();
            Size currentMinSize = getMinSize();
            if ((currentMinSize.width < contentMinSize.width) || (currentMinSize.height < contentMinSize.height))
                setMinSize(contentMinSize);
            
            // TODO: May conflict with eventThread.
            Size contentMaxSize = VBox::getMaxSize();
            Size currentMaxSize = getMaxSize();
            if ((currentMaxSize.width > contentMaxSize.width) || (currentMaxSize.height > contentMaxSize.height))
                setMaxSize(contentMaxSize);
            
            VBox::setSize(rEvent->getSize());
            m_draw = true;
        }
    }
}
