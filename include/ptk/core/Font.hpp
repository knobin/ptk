//
//  core/Font.hpp
//  pTK
//
//  Created by Robin Gustafsson on 2019-07-14.
//

#ifndef PTK_CORE_FONT_HPP
#define PTK_CORE_FONT_HPP

// Local Headers
#include "ptk/core/Types.hpp"
#include "ptk/util/Size.hpp"

// C++ Headers
#include <string>

// Skia Headers
#include "include/core/SkFont.h"
#include "include/core/SkTypeface.h"

namespace pTK
{
    /** Font class implementation.
     
        This class is for handling font information.
    */
    class Font
    {
    public:
        /** Constructs Font with default values.
         
            @return    default initialized Font
        */
        Font();

        /** Deconstructor for Font.

        */
        virtual ~Font() = default;
       
        /** Function for setting the font from a given file.
         
            @param path    font file to load
            @return        status
        */
        bool loadFromFile(const std::string& path);

        /** Function for setting the font family of the Label.
         
            @param font    font family for Label to use
            @return        status
        */
        bool setFamily(const std::string& fontFamily);
        
        /** Function for retrieving the current font family used by Label.
         
            @return  current font family
        */
        std::string getFamily() const;
        
        /** Function for setting the font size of the Label
         
            @param fontSize    size of the font
        */
        void setSize(uint fontSize);
        
        /** Function for retrieving the current font size used by Label.
         
            @return  current font size
        */
        uint getSize() const;
        
        /** Function for retrieving the bounds of a specific text.
         
            @param str     text to calculate bounds on
            @return        bounds of the text
        */
        Size getBounds(const std::string& str) const;
        
        /** Function for retrieving the raw SkFont.
         
         @return  raw SkFont
         */
        const SkFont* skFont() const;

    private:
        SkFont m_font;
    };
}


#endif // PTK_CORE_FONT_HPP


