//
//  core/Sizable.hpp
//  pTK
//
//  Created by Robin Gustafsson on 2019-07-11.
//

#ifndef PTK_CORE_SIZABLE_HPP
#define PTK_CORE_SIZABLE_HPP

// Local Headers
#include "ptk/util/Size.hpp"
#include "ptk/core/Types.hpp"

namespace pTK
{
    /** Sizable class implementation.

        Sizable class for handling size.
    */
    class Sizable
    {
    public:
        /** Constructs Sizable with default values.

            @return  default initialized Sizable
        */
        Sizable();

        /** Constructs Sizable with default values with size.

            @return  default initialized Sizable
        */
        Sizable(const Size& size);

        /** Deconstructor for Sizable.

        */
        virtual ~Sizable() = default;

        /** Funtion for setting minimal size.

            @param size    minimal size
        */
        void setMinSize(const Size& size);

        /** Funtion for getting the minimal size.

            @return    minimal size
        */
        Size getMinSize() const;

        /** Funtion for setting size.

            @param size    size
        */
        void setSize(const Size& size);

        /** Funtion for setting size.

            @param size    size
        */
        void setConstSize(const Size& size);

        /** Funtion for getting the size.

            @return    size
        */
        const Size& getSize() const;

        /** Funtion for setting maximal size.

            @param size    maximal size
        */
        void setMaxSize(const Size& size);

        /** Funtion for getting the maximal size.

            @return    maximal size
        */
        Size getMaxSize() const;

        /** Funtion for setting both minimal and maximal size.

            @param min    minimal size
            @param max    maximum size
        */
        void setLimits(const Size& min, const Size& max);

        /** Function for checking if Sizable object has a const size.

            @return    status
         */
        bool isConstSize() const;

    private:
        /** Funtion for knowing when the size has been changed.

            Will be called when setSize accepts a new size.
            Internal size will be set before calling this, so
            calling getSize will also return the new size.

            @param size    new size
        */
        virtual void onResize(const Size&) {}

        /** Funtion for knowing when the limits has been changed.

            Will be called when when either setMinSize, setMaxSize or setLimits
            accepts a new size.
            Internal sizes will be set before calling this, so
            calling getMaxSize or getMinSize will also return the new size.

            @param min    current min size
            @param max    current max size
        */
        virtual void onLimitChange(const Size&, const Size&) {}

    private:
        Size m_minSize;
        Size m_size;
        Size m_maxSize;

        bool m_minLock;
        bool m_maxLock;
    };

    // Comparison operators.
    bool operator==(const Sizable& lhs, const Sizable& rhs);
    bool operator!=(const Sizable& lhs, const Sizable& rhs);
}


#endif // PTK_CORE_SIZABLE_HPP
