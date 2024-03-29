//
//  core/Sizable.cpp
//  pTK
//
//  Created by Robin Gustafsson on 2019-07-11.
//

// pTK Headers
#include "ptk/core/Sizable.hpp"

namespace pTK
{
    Sizable::Sizable() noexcept
        : m_minSize{pTK::Size::Min},
          m_size{pTK::Size::Min},
          m_maxSize{pTK::Size::Max}
    {}

    Sizable::Sizable(const Size& size) noexcept
        : m_minSize{pTK::Size::Min},
          m_size{size},
          m_maxSize{pTK::Size::Max}
    {}

    Sizable::Sizable(const Size& min, const Size& size, const Size& max) noexcept
        : m_minSize{size},
          m_size{size},
          m_maxSize{size}
    {
        Size minSize{(size.width > min.width) ? min.width : size.width,
                     (size.height > min.height) ? min.height : size.height};
        Size maxSize{(max.width > size.width) ? max.width : size.width,
                     (max.height > size.height) ? max.height : size.height};

        setMinSize(minSize);
        setMaxSize(maxSize);
    }

    void Sizable::setMinSize(const Size& size)
    {
        if (size == getMinSize())
            return;

        // Update minimal sizes.
        uint8_t status{updateMinWidth(size.width)};
        status |= updateMinHeight(size.height);

        // Signal a size change.
        if (status & 1) // Check if first bit is set.
            onSizeChange(getSize());

        // Signal a limit change.
        if (status & 2) // Check if second bit is set.
            onLimitChange(getMinSize(), getMaxSize());
    }

    Size Sizable::getMinSize() const noexcept
    {
        return m_minSize;
    }

    void Sizable::setSize(const Size& size)
    {
        if (size == getSize())
            return;

        uint8_t bits{updateWidth(size.width)};
        bits |= updateHeight(size.height);

        // Signal size change.
        if (bits & 1)
            onSizeChange(getSize());

        // Signal limit change.
        if (bits & 2)
            onLimitChange(getMinSize(), getMaxSize());
    }

    const Size& Sizable::getSize() const noexcept
    {
        return m_size;
    }

    void Sizable::setMaxSize(const Size& size)
    {
        if (size == getMaxSize())
            return;

        // Update maximum sizes.
        uint8_t status{updateMaxWidth(size.width)};
        status |= updateMaxHeight(size.height);

        // Signal a size change.
        if (status & 1) // Check if first bit is set.
            onSizeChange(getSize());

        // Signal a limit change.
        if (status & 2) // Check if second bit is set.
            onLimitChange(getMinSize(), getMaxSize());
    }

    Size Sizable::getMaxSize() const noexcept
    {
        return m_maxSize;
    }

    void Sizable::setLimits(const Limits& limits)
    {
        setLimits(limits.min, limits.max);
    }

    void Sizable::setLimits(const Size& min, const Size& max)
    {
        // Update minimal sizes.
        uint8_t s1{updateMinWidth(min.width)};
        s1 |= updateMinHeight(min.height);

        // Update maximum sizes.
        uint8_t s2{updateMaxWidth(max.width)};
        s2 |= updateMaxHeight(max.height);

        // Signal a size change.
        if ((s1 & 1) || ((s2 & 1)))
            onSizeChange(getSize());

        // Signal a limit change.
        if ((s1 & 2) || ((s2 & 2)))
            onLimitChange(getMinSize(), getMaxSize());
    }

    Limits Sizable::getLimits() const noexcept
    {
        return {m_minSize, m_maxSize};
    }

    void Sizable::updateMinSize(const Size& size)
    {
        updateMinWidth(size.width);
        updateMinHeight(size.height);
    }

    void Sizable::updateSize(const Size& size)
    {
        updateWidth(size.width);
        updateHeight(size.height);
    }

    void Sizable::updateMaxSize(const Size& size)
    {
        updateMaxWidth(size.width);
        updateMaxHeight(size.height);
    }

    uint8_t Sizable::updateMinWidth(const Size::value_type width)
    {
        uint8_t status{0};
        const Size::value_type maxWidth{getMaxSize().width};

        if ((width >= Size::Limits::Min) && (width <= maxWidth))
        {
            // If new minimal width is larger than current size. Set width to minimal width.
            if (width > m_size.width)
            {
                m_size.width = width;
                status = 1;
            }

            if (width != m_minSize.width)
            {
                // Update minimal width.
                m_minSize.width = width;
                status |= 2;
            }
        }
        else if (width >= Size::Limits::Min)
        {
            // new minimal width is bigger than the max width.

            m_minSize.width = width;
            m_size.width = width;
            m_maxSize.width = width;

            status = 3;
        }

        return status;
    }

    uint8_t Sizable::updateMinHeight(const Size::value_type height)
    {
        uint8_t status{0};
        const Size::value_type maxHeight{getMaxSize().height};

        if ((height >= Size::Limits::Min) && (height <= maxHeight))
        {
            // If new minimal height is larger than current size. Set height to minimal height.
            if (height > m_size.height)
            {
                m_size.height = height;
                status = 1;
            }

            if (height != m_minSize.height)
            {
                // Update minimal height.
                m_minSize.height = height;
                status |= 2;
            }
        }
        else if (height >= Size::Limits::Min)
        {
            // new minimal width is bigger than the max width.

            m_minSize.height = height;
            m_size.height = height;
            m_maxSize.height = height;

            status = 3;
        }

        return status;
    }

    uint8_t Sizable::updateWidth(Size::value_type width)
    {
        const Size::value_type minWidth{getMinSize().width};
        const Size::value_type currWidth{getSize().width};
        const Size::value_type maxWidth{getMaxSize().width};

        if ((minWidth == currWidth) && (currWidth == maxWidth))
        {
            m_minSize.width = width;
            m_size.width = width;
            m_maxSize.width = width;

            return 3;
        }
        else
        {
            // In range.
            if ((width >= minWidth) && (width <= maxWidth))
            {
                // Update width.
                m_size.width = width;
                return 1;
            }
            else
            {
                uint8_t status{0};

                // Min width
                if (width < minWidth)
                {
                    m_size.width = width;
                    m_minSize.width = width;

                    status = 3;
                }

                // Max width
                if (width > m_maxSize.width)
                {
                    m_size.width = width;
                    m_maxSize.width = width;

                    status = 3;
                }

                return status;
            }
        }
    }

    uint8_t Sizable::updateHeight(Size::value_type height)
    {
        const Size::value_type minHeight{getMinSize().height};
        const Size::value_type currHeight{getSize().height};
        const Size::value_type maxHeight{getMaxSize().height};

        if ((minHeight == currHeight) && (currHeight == maxHeight))
        {
            m_minSize.height = height;
            m_size.height = height;
            m_maxSize.height = height;

            return 3;
        }
        else
        {
            // In range.
            if ((height >= minHeight) && (height <= maxHeight))
            {
                // Update height
                m_size.height = height;
                return 1;
            }
            else
            {
                uint8_t status{0};

                // Min height
                if (height < minHeight)
                {
                    m_size.height = height;
                    m_minSize.height = height;

                    status = 3;
                }

                // Max height
                if (height > m_maxSize.height)
                {
                    m_size.height = height;
                    m_maxSize.height = height;

                    status = 3;
                }

                return status;
            }
        }
    }

    uint8_t Sizable::updateMaxWidth(const Size::value_type width)
    {
        uint8_t status{0};
        const Size::value_type minWidth{getMinSize().width};

        if ((width >= minWidth) && (width <= Size::Limits::Max))
        {
            // If new maximum width is smaller than current size. Set width to maximum width.
            if (width < m_size.width)
            {
                m_size.width = width;
                status = 1;
            }

            if (width != m_maxSize.width)
            {
                // Update maximum width.
                m_maxSize.width = width;
                status |= 2;
            }
        }
        else if (width <= Size::Limits::Max)
        {
            // new maximum width is smaller than the min width.

            m_minSize.width = width;
            m_size.width = width;
            m_maxSize.width = width;

            status = 3;
        }

        return status;
    }

    uint8_t Sizable::updateMaxHeight(const Size::value_type height)
    {
        uint8_t status{0};
        const Size::value_type minHeight{getMinSize().height};

        if ((height >= minHeight) && (height <= Size::Limits::Max))
        {
            // If new maximum height is smaller than current size. Set height to maximum height.
            if (height < m_size.height)
            {
                m_size.height = height;
                status = 1;
            }

            if (height != m_maxSize.height)
            {
                // Update maximum height.
                m_maxSize.height = height;
                status |= 2;
            }
        }
        else if (height <= Size::Limits::Max)
        {
            // new maximum width is smaller than the min width.

            m_minSize.height = height;
            m_size.height = height;
            m_maxSize.height = height;

            status = 3;
        }

        return status;
    }

    // Comparison operators.
    bool operator==(const Sizable& lhs, const Sizable& rhs)
    {
        return ((lhs.getMinSize() == rhs.getMinSize()) && (lhs.getSize() == rhs.getSize()) &&
                (lhs.getMaxSize() == rhs.getMaxSize()));
    }

    bool operator!=(const Sizable& lhs, const Sizable& rhs)
    {
        return !(lhs == rhs);
    }
} // namespace pTK
