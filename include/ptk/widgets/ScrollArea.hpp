//
//  widgets/ScrollArea.hpp
//  pTK
//
//  Created by Robin Gustafsson on 2020-02-06.
//

#ifndef PTK_WIDGETS_SCROLLAREA_HPP
#define PTK_WIDGETS_SCROLLAREA_HPP

// Local Headers
#include "ptk/core/Box.hpp"
#include "ptk/widgets/Rectangle.hpp"

namespace pTK
{
    /** ScrollArea class implementation.

        TODO: Add description
    */
    class ScrollArea : public Box
    {
    public:
        /** Constructs ScrollArea with default values.

            @return    default initialized ScrollArea
        */
        ScrollArea();

        /** Deconstructor for ScrollArea.

        */
        virtual ~ScrollArea() = default;

        bool onScrollEvent(const Vec2f& vec) override;

        void onDraw(SkCanvas* canvas) override;

    private:
        void onAdd(const Ref<Widget>&) override;
        void onRemove(const Ref<Widget>&) override;
        void onChildUpdate(size_type) override;
        void onResize(const Size& size) override;

    private:
        void drawScrollBar(const Point& pos, SkCanvas* canvas);

    private:
        size_type m_startID;
        Rectangle m_rect;
    };
}

#endif // PTK_WIDGETS_SCROLLAREA_HPP
