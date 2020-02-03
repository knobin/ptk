//
//  core/Widget.cpp
//  pTK
//
//  Created by Robin Gustafsson on 2019-06-19.
//

// Local Headers
#include "ptk/core/Widget.hpp"

namespace pTK
{
    Widget::Widget()
        : Drawable(), EventHandling(), Sizable(), m_parent{nullptr}, m_name{},
            m_margin{}, m_align{Align::Center}
    {
        
    }
    
    void Widget::setParent(Widget* parent)
    {
        m_parent = parent;
    }
    
    Widget* Widget::getParent() const
    {
        return m_parent;
    }

    void Widget::onResize(const Size& size)
    {
        update();
    }

    void Widget::onLimitChange(const Size&, const Size&)
    {
        update();
    }
    
    void Widget::setPosHint(const Point& pos)
    {
        m_pos = pos;
        update();
    }
    
    const Point& Widget::getPosition() const
    {
        return m_pos;
    }
    
    void Widget::setName(const std::string& name)
    {
        m_name = name;
    }
    
    const std::string& Widget::getName() const
    {
        return m_name;
    }
    
    void Widget::setMargin(const Margin& margin)
    {
        m_margin = margin;
        update();
    }
    
    void Widget::setMarginTop(Margin::value_type topMargin)
    {
        m_margin.top = topMargin;
        update();
    }
    
    void Widget::setMarginBottom(Margin::value_type bottomMargin)
    {
        m_margin.bottom = bottomMargin;
        update();
    }
    
    void Widget::setMarginLeft(Margin::value_type leftMargin)
    {
        m_margin.left = leftMargin;
        update();
    }
    
    void Widget::setMarginRight(Margin::value_type rightMargin)
    {
        m_margin.right = rightMargin;
        update();
    }
    
    void Widget::setMarginTopBottom(Margin::value_type topMargin, Margin::value_type bottomMargin)
    {
        m_margin.top = topMargin;
        m_margin.bottom = bottomMargin;
        update();
    }
    
    void Widget::setMarginLeftRight(Margin::value_type leftMargin, Margin::value_type rightMargin)
    {
        m_margin.left = leftMargin;
        m_margin.right = rightMargin;
        update();
    }
    
    const Margin& Widget::getMargin() const
    {
        return m_margin;
    }
    
    int32 Widget::getMarginTop() const
    {
        return m_margin.top;
    }
    
    int32 Widget::getMarginBottom() const
    {
        return m_margin.bottom;
    }
    
    int32 Widget::getMarginLeft() const
    {
        return m_margin.left;
    }
    
    int32 Widget::getMarginRight() const
    {
        return m_margin.right;
    }

    void Widget::setAlign(std::underlying_type<Align>::type alignment)
    {
        m_align = alignment;
        update();
    }

    std::underlying_type<Align>::type Widget::getAlign() const
    {
        return m_align;
    }
    
    bool Widget::updateChild(Widget*)
    {
        return true;
    }
    
    bool Widget::update()
    {
        if (m_parent != nullptr)
            return m_parent->updateChild(this);
        
        return false;
    }
    
    bool Widget::drawChild(Widget*)
    {
        return true;
    }
    
    bool Widget::draw()
    {
        if (m_parent != nullptr)
            return m_parent->drawChild(this);
        
        return false;
    }
    
    ///////////////////////////////////////////////////////////////////////////////
    
    // Comparison operators.
    bool operator==(const Widget& lhs, const Widget& rhs)
    {
        return ((lhs.getPosition() == rhs.getPosition()) &&
                (lhs.getSize() == rhs.getSize()) &&
                (lhs.getName() == rhs.getName()) &&
                (lhs.getParent() == rhs.getParent()));
    }
    
    bool operator!=(const Widget& lhs, const Widget& rhs)
    {
        return !(lhs == rhs);
    }
}
