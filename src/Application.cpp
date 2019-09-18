//
//  Application.cpp
//  pTK
//
//  Created by Robin Gustafsson on 2019-06-13.
//

// Local Headers
#include "ptk/Application.hpp"
#include "ptk/util/Clock.hpp"
#include "ptk/Log.hpp"

// C++ Headers
#include <thread>

namespace pTK
{
    Application::Application()
        : Singleton()
    {
        Log::init();
    }
    
    Application::Application(int, char* [])
        : Singleton()
    {
        Log::init();
        // TODO: Check arguments.
    }

    int Application::exec(pTK::Window* window)
    {
        PTK_ASSERT(window, "Window is nullptr");
        
        window->show();
        
        // Render loop.
        while (!window->shouldClose())
        {
            // Events
            window->pollEvents();

            // To lower cpu usage, we wait.
            std::this_thread::sleep_for(std::chrono::milliseconds(32));
        }
        
        window->hide();

        return 0;
    }
}
