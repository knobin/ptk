//
//  util/Size.cpp
//  pTK
//
//  Created by Robin Gustafsson on 2019-06-24.
//

// Local Headers
#include "ptk/util/Size.hpp"

namespace pTK
{
    Size::Size()
        : width{0.0f}, height{0.0f}
    {
        
    }
    
    Size::Size(float t_width, float t_height)
        : width{t_width}, height{t_height}
    {
        
    }
    
    void Size::setSize(float t_width, float t_height)
    {
        width = t_width;
        height = t_height;
    }
    
    // Comparison operators.
    bool operator==(const Size& lhs, const Size& rhs)
    {
        return ((lhs.width == rhs.width) && (lhs.height == rhs.height));
    }
    
    bool operator!=(const Size& lhs, const Size& rhs)
    {
        return !(lhs == rhs);
    }
    
    // Binary arithmetic operators.
    Size operator+(const Size& lhs, const Size& rhs)
    {
        Size newSize;
        newSize.width = lhs.width + rhs.width;
        newSize.height = lhs.height + rhs.height;
        
        return newSize;
    }
    
    Size operator-(const Size& lhs, const Size& rhs)
    {
        Size newSize;
        newSize.width = lhs.width - rhs.width;
        newSize.height = lhs.height - rhs.height;
        
        return newSize;
    }
    
    Size operator*(const Size& lhs, const Size& rhs)
    {
        Size newSize;
        newSize.width = lhs.width * rhs.width;
        newSize.height = lhs.height * rhs.height;
        
        return newSize;
    }
    
    Size operator/(const Size& lhs, const Size& rhs)
    {
        Size newSize;
        newSize.width = lhs.width / rhs.width;
        newSize.height = lhs.height / rhs.height;
        
        return newSize;
    }
    
    Size& operator+=(Size& lhs, const Size& rhs)
    {
        return lhs = lhs + rhs;
    }
    
    Size& operator-=(Size& lhs, const Size& rhs)
    {
        return lhs = lhs - rhs;
    }
    
    Size& operator*=(Size& lhs, const Size& rhs)
    {
        return lhs = lhs * rhs;
    }
    
    Size& operator/=(Size& lhs, const Size& rhs)
    {
        return lhs = lhs / rhs;
    }
}