//
//  util/Align.cpp
//  pTK
//
//  Created by Robin Gustafsson on 2019-07-29s.
//

// Local Headers
#include "ptk/util/Alignment.hpp"

namespace pTK
{
    bool isAlignSet(int32 number, Align align)
    {
        return ((number & align) == align);
    }
    
    Margin::Margin()
        : Directions{0, 0, 0, 0}
    {
    }

    Margin::Margin(Directions directions)
        : Directions{directions}
    {
    }
    
    Margin::Margin(int32 mTop, int32 mBottom, int32 mLeft, int32 mRight)
        : Directions{mTop, mBottom, mLeft, mRight}
    {
    }
}