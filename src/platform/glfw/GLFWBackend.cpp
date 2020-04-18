//
//  Window.cpp
//  pTK
//
//  Created by Robin Gustafsson on 2019-06-12.
//

// Local Headers
#include "ptk/platform/glfw/GLFWBackend.hpp"
#include "ptk/Window.hpp"
#include "ptk/events/KeyEvent.hpp"
#include "ptk/events/MouseEvent.hpp"
#include "ptk/events/WindowEvent.hpp"
#include "ptk/util/Semaphore.hpp"
#include "ptk/Core.hpp"

namespace pTK
{
    GLFWBackend::GLFWBackend(Window *window, const std::string& name, const Size& size, Backend backend)
        : WindowBackend(backend),
            m_window{nullptr}, m_drawCanvas{nullptr}, m_parentWindow{window}, m_scale{1.0f, 1.0f}
    {
        initGLFW();

        // Create Window.
        m_window = glfwCreateWindow(static_cast<int>(size.width), static_cast<int>(size.height), name.c_str(), nullptr, nullptr);
        PTK_ASSERT(m_window, "Failed to create GLFW Window");
        PTK_INFO("GLFW Window Created, {0:d}x{1:d}", static_cast<int>(size.width), static_cast<int>(size.height));

        // Get Monitor Scale
        glfwGetWindowContentScale(m_window, &m_scale.x, &m_scale.y);
        PTK_INFO("Monitor scale, {0:0.2f}x{1:0.2f}", m_scale.x, m_scale.y);

        // Bind context.
        glfwMakeContextCurrent(m_window);

        // Init Canvas
        Size wSize;
        wSize.width = static_cast<Size::value_type>(size.width * m_scale.x);
        wSize.height = static_cast<Size::value_type>(size.height * m_scale.y);
        m_drawCanvas = std::make_unique<GLContext>(Size(wSize.width, wSize.height));
        PTK_ASSERT(m_drawCanvas, "Failed to create Canvas");

        // Set Callbacks
        glfwSetWindowUserPointer(m_window, m_parentWindow);
        setWindowCallbacks();
        setMouseCallbacks();
        setKeyCallbacks();

        PTK_INFO("Window Initialization finished");
    }

    // Init Functions
    void GLFWBackend::initGLFW()
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
    void GLFWBackend::setWindowCallbacks()
    {
        // void window_size_callback(GLFWwindow* window, int width, int height)
        glfwSetWindowSizeCallback(m_window, [](GLFWwindow* t_window, int t_width, int t_height){
            auto window = static_cast<Window*>(glfwGetWindowUserPointer(t_window));
            window->postEvent(new ResizeEvent{static_cast<Size::value_type>(t_width), static_cast<Size::value_type>(t_height)});
            window->handleEvents();
        });

        // void window_close_callback(GLFWwindow* window)
        glfwSetWindowCloseCallback(m_window, [](GLFWwindow* t_window){
            auto window = static_cast<Window*>(glfwGetWindowUserPointer(t_window));
            window->postEvent(new Event{Event::Category::Window, Event::Type::WindowClose});
        });

        // void window_maximize_callback(GLFWwindow* window, int maximized)
        glfwSetWindowMaximizeCallback(m_window, [](GLFWwindow* t_window, int){
            // TODO: Should create a resize EventFunction.
            auto window = static_cast<Window*>(glfwGetWindowUserPointer(t_window));
            int width, height;
            glfwGetWindowSize(t_window, &width, &height);
            window->postEvent(new ResizeEvent{static_cast<Size::value_type>(width), static_cast<Size::value_type>(height)});
        });
    }

    void GLFWBackend::setMouseCallbacks()
    {
        // void cursor_enter_callback(GLFWwindow* window, int entered)
        glfwSetCursorEnterCallback(m_window,[](GLFWwindow* t_window, int entered){
            if (!entered)
            {
                auto window = static_cast<Window*>(glfwGetWindowUserPointer(t_window));
                MotionEvent event{-1, -1};
                window->sendEvent(&event);
            }
        });

        // void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
        glfwSetCursorPosCallback(m_window, [](GLFWwindow* t_window, double t_xpos, double t_ypos){
            auto window = static_cast<Window*>(glfwGetWindowUserPointer(t_window));
            Size wSize = window->getSize();

            if ((t_xpos >= 0) && (t_xpos <= (wSize.width)))
            {
                if ((t_ypos >= 0) && (t_ypos <= (wSize.height)))
                {
                    MotionEvent event{ static_cast<Point::value_type>(t_xpos),
                        static_cast<Point::value_type>(t_ypos)};
                    window->sendEvent(&event);
                }
            }


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
            {
                ButtonEvent event{Event::Type::MouseButtonPressed,
                    button,
                    static_cast<Point::value_type>(xpos),
                    static_cast<Point::value_type>(ypos)};
                window->sendEvent(&event);
            }
            else if (t_action == GLFW_RELEASE)
            {
                ButtonEvent event{Event::Type::MouseButtonReleased,
                    button,
                    static_cast<Point::value_type>(xpos),
                    static_cast<Point::value_type>(ypos)};
                window->sendEvent(&event);
            }
        });

        // void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
        glfwSetScrollCallback(m_window, [](GLFWwindow* t_window, double xoffset, double yoffset){
            auto window = static_cast<Window*>(glfwGetWindowUserPointer(t_window));
            Vec2f v{static_cast<float>(xoffset), static_cast<float>(yoffset)};
            ScrollEvent event{v};
            window->sendEvent(&event);
        });
    }

    void GLFWBackend::setKeyCallbacks()
    {
        // void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        glfwSetKeyCallback(m_window, [](GLFWwindow* t_window, int t_key, int, int t_action, int){
            auto window = static_cast<Window*>(glfwGetWindowUserPointer(t_window));
            if (t_action == GLFW_PRESS)
            {
                KeyEvent event{Event::Type::KeyPressed, t_key};
                window->sendEvent(&event);
            }
            else if (t_action == GLFW_RELEASE)
            {
                KeyEvent event{ Event::Type::KeyReleased, t_key };
                window->sendEvent(&event);
            }
        });
    }

    GLFWBackend::~GLFWBackend()
    {
		// Free canvas before glfw to avoid OpenGL errors.
		m_drawCanvas.reset(nullptr);
        glfwDestroyWindow(m_window);
		glfwTerminate();
        PTK_INFO("Window Destroyed");
    }

    void GLFWBackend::setPosHint(const Point& pos)
    {
        glfwSetWindowPos(m_window, pos.x, pos.y);
    }

    void GLFWBackend::pollEvents()
    {
        glfwWaitEvents();
    }

    void GLFWBackend::swapBuffers()
    {
        glfwSwapBuffers(m_window);
    }

    void GLFWBackend::resize(const Size&)
    {
        m_drawCanvas->resize(m_parentWindow->getContentSize());
    }

    void GLFWBackend::setLimits(const Size& min, const Size& max)
    {
        setLimits2(min, max);
    }

    void GLFWBackend::setLimits2(const Size& minSize, const Size& maxSize)
    {
        if (m_window)
        {
            int width = (maxSize.width == Size::Limits::Max) ? GLFW_DONT_CARE : maxSize.width;
            int height = (maxSize.height == Size::Limits::Max) ? GLFW_DONT_CARE : maxSize.height;
            glfwSetWindowSizeLimits(m_window, static_cast<int>(minSize.width), static_cast<int>(minSize.height), width, height);
        }
    }

    void GLFWBackend::close()
    {
        glfwSetWindowShouldClose(m_window, GLFW_TRUE);
        m_parentWindow->postEvent(new Event{Event::Category::Window, Event::Type::WindowClose});
    }

    // Visible
    void GLFWBackend::show()
    {
        glfwShowWindow(m_window);
        m_parentWindow->forceDrawAll();
    }

    void GLFWBackend::hide()
    {
        glfwHideWindow(m_window);
    }

    ContextBase *GLFWBackend::getContext() const
    {
        return m_drawCanvas.get();
    }

    Vec2f GLFWBackend::getDPIScale() const
    {
        return m_scale;
    }
}
