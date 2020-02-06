//
//  core/ScrollArea.cpp
//  pTK
//
//  Created by Robin Gustafsson on 2020-02-06.
//

// Local Headers
#include "ptk/widgets/ScrollArea.hpp"

namespace pTK
{
    ScrollArea::ScrollArea()
        : Box(), m_startID{0}, m_rect{}
    {
        m_rect.setColor(Color(0x000000FF));
    }

    bool ScrollArea::onScrollEvent(const Vec2f& offset)
    {
        // Send the event to the base class (Box) and if the event is not
        // handled by one of the children it will return false.
        // i.e. we handle it here.
        if (!Box::onScrollEvent(offset))
        {
            if (!empty())
            {
                for (auto& it : *this)
                {
                    Point pos{it->getPosition()};
                    pos.y += static_cast<Point::value_type>(offset.y*20);
                    it->setPosHint(pos);
                }
            }
        }
        
        return true;
    }

    void ScrollArea::onDraw(SkCanvas* canvas)
    {
        // Set Size and Point
        SkPoint vbPos{convertToSkPoint(getPosition())};
        SkPoint vbSize{convertToSkPoint(getSize())};
        vbSize += vbPos; // skia needs the size to be pos+size.

        // Set Color
        SkPaint paint;
        paint.setAntiAlias(true);
        Color bg{getBackground()};
        paint.setARGB(bg.a, bg.r, bg.g, bg.b);

        // Draw Rect
        SkRect rect{};
        rect.set(vbPos, vbSize);
        paint.setStyle(SkPaint::kStrokeAndFill_Style);
        canvas->drawRoundRect(rect, 0, 0, paint);

        canvas->save();
        canvas->clipRect(rect, true);
        Point position{getPosition()};
        for(size_type i{m_startID}; i < size(); ++i)
            at(i)->onDraw(canvas);
        drawScrollBar({position.x + getSize().width - 10, position.y}, canvas);
        canvas->restore();
    }

    void ScrollArea::onAdd(const Ref<Widget>&)
    {
        // TODO: When a child is added.
        Point pos{getPosition()};
        Size vbSize{};

        for (const auto& it : *this)
        {
            it->setPosHint(pos);
            Size size{it->getSize()};
            pos.y += static_cast<Point::value_type>(size.height);

            vbSize.height += static_cast<Point::value_type>(size.height);
            if (static_cast<Point::value_type>(size.width) > vbSize.width)
                vbSize.width = static_cast<Point::value_type>(size.width);
        }

        setSize(vbSize);
    }

    void ScrollArea::onRemove(const Ref<Widget>&)
    {
        // TODO: When a child is removed.
    }

    void ScrollArea::onChildUpdate(size_type)
    {
        // TODO: When a child is updated.
    }

    void ScrollArea::onResize(const Size& size)
    {
        // TODO: When the ScrollArea is resized.
        m_rect.setSize(Size{10, size.height});
    }

    void ScrollArea::drawScrollBar(const Point& pos, SkCanvas* canvas)
    {
        m_rect.setPosHint(pos);
        Size s{m_rect.getSize()};
        Point p{m_rect.getPosition()};
        m_rect.onDraw(canvas);
    }
}