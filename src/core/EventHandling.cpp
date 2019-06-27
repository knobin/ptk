//
//  core/EventHandling.cpp
//  pTK
//
//  Created by Robin Gustafsson on 2019-06-13.
//

// Local Headers
#include "ptk/core/EventHandling.hpp"

namespace pTK
{

    EventHandling::EventHandling()
        : EventCallbacks(), EventFunctions()
    {
    }
    
    bool EventHandling::handleKeyEvent(EventType type, int keycode)
    {
        bool rValue = onKeyEvent(type, keycode);
        if (m_keyCallback != nullptr)
            rValue |= m_keyCallback(type, keycode);
        
        return rValue;
    }
    
    bool EventHandling::handleHoverEvent()
    {
        bool rValue = onHoverEvent();
        if (m_hoverCallback != nullptr)
            rValue |= m_hoverCallback();
        
        return rValue;
    }
    
    bool EventHandling::handleLeaveEvent()
    {
        bool rValue = onLeaveEvent();
        if (m_leaveCallback != nullptr)
            rValue |= m_leaveCallback();
        
        return rValue;
    }
    
    bool EventHandling::handleScrollEvent(const Vec2<int>& offset)
    {
        bool rValue = onScrollEvent(offset);
        if (m_scrollCallback != nullptr)
            rValue |= m_scrollCallback(offset);
        
        return rValue;
    }
    
    bool EventHandling::handleClickEvent(MouseButton button, const Vec2<int>& position)
    {
        bool rValue = onClickEvent(button, position);
        rValue = false;
        if (m_clickCallback != nullptr)
            rValue |= m_clickCallback(button, position);
        
        return rValue;
    }
    
    bool EventHandling::handleReleaseEvent(MouseButton button, const Vec2<int>& position)
    {
        bool rValue = onReleaseEvent(button, position);
        if (m_releaseCallback != nullptr)
            rValue |= m_releaseCallback(button, position);
        
        return rValue;
    }
}