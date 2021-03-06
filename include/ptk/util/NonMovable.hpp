//
//  util/NonMovable.hpp
//  pTK
//
//  Created by Robin Gustafsson on 2019-06-29.
//

#ifndef PTK_UTIL_NONMOVABLE_HPP
#define PTK_UTIL_NONMOVABLE_HPP

namespace pTK
{
    /** NonMovable class implementation.
     
        Class for forbidding moving.
    */
    class NonMovable
    {
    public:
        /** Deleted Move Constructor.

        */
        NonMovable(const NonMovable&) = delete;

        /** Deleted Move Assignment operator.

        */
        NonMovable& operator=(const NonMovable&) = delete;
        
    protected:
        NonMovable() = default;
    };
}

#endif // PTK_UTIL_NONMOVABLE_HPP

