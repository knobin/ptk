//
//  util/color.hpp
//  pTK
//
//  Created by Robin Gustafsson on 2019-06-17.
//

#ifndef PTK_UTIL_COLOR_HPP
#define PTK_UTIL_COLOR_HPP

// C++ Headers
#include <cstdint>

namespace pTK
{
    union u_color
    {
        struct s_color
        {
            uint8_t a;
            uint8_t b;
            uint8_t g;
            uint8_t r;
        } rgba;
        
        uint32_t data;
    };
    
    class Color
    {
    public:
        Color();
        explicit Color(uint32_t color);
        Color(uint8_t red, uint8_t green, uint8_t blue);
        Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
        virtual ~Color() = default;
        
        // Copy.
        Color(const Color& rhs);
        
        // Assignment.
        Color& operator=(Color rhs);
        
        // Get.
        uint8_t get_r() const;
        uint8_t get_g() const;
        uint8_t get_b() const;
        uint8_t get_a() const;
        Color get_color() const;
        uint32_t get_raw() const;
        
        // Set.
        void set_r(uint8_t red);
        void set_g(uint8_t green);
        void set_b(uint8_t blue);
        void set_a(uint8_t alpha);
        void set_rgb(uint8_t red, uint8_t green, uint8_t blue);
        void set_rgba(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
        void set_color(const Color& value);
        void set_color(uint32_t color);
        
        // Binary arithmetic operators.
        Color operator+(const Color& rhs) const;
        Color& operator+=(const Color& rhs);
        Color operator-(const Color& rhs) const;
        Color& operator-=(const Color& rhs);
        
        // Comparison operators.
        bool operator==(const Color& rhs) const;
        bool operator!=(const Color& rhs) const;
        
    protected:
        u_color m_color;
    };
}

#endif // PTK_UTIL_COLOR_HPP
