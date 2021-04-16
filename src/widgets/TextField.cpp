//
//  widgets/TextField.cpp
//  pTK
//
//  Created by Robin Gustafsson on 2021-04-10.
//

// pTK Headers
#include "ptk/widgets/TextField.hpp"

// C++ Headers
#include <cctype>

// Skia Headers
PTK_DISABLE_WARN_BEGIN()
#include "include/core/SkFontMetrics.h"
PTK_DISABLE_WARN_END()

namespace pTK
{
    TextField::TextField()
        : Rectangle(), Text()
    {
        onKey([this](Event::Type type, KeyCode keycode, byte modifier){
            if (type == Event::Type::KeyPressed)
                handleKeyPress(keycode, modifier);
            return false;
        });

        onClick([this](Mouse::Button, const Point&){
            m_drawCursor = true;
            return false;
        });

        onLeaveClick([this](){
            m_drawCursor = false;
            return false;
        });
    }

    void TextField::handleKeyPress(KeyCode keycode, byte modifier)
    {
        if (IsKeyCodeAlpha(keycode) || IsKeyCodeDigit(keycode) || IsKeyCodeSpace(keycode))
        {
            addToText(keycode, modifier);
        }
        else
        {
            switch (keycode) {
                case Key::Backspace:
                case Key::Delete:
                {
                    removeFromText(((keycode == Key::Delete) ? 1 : -1));
                    break;
                }
                case Key::Left:
                case Key::Right:
                {
                    moveCursor(((keycode == Key::Left) ? -1 : 1), getText().size(), true);
                    break;
                }
                case Key::Home:
                case Key::End:
                {
                    moveCursorToPos(((keycode == Key::Home) ? 0 : getText().size()), getText().size(), true);
                    break;
                }
                default:
                    break;
            }
        }
    }

    void TextField::addToText(KeyCode keycode, byte modifier)
    {
        bool shift = IsKeyEventModifierSet(modifier, KeyEvent::Modifier::Shift);
        bool capsLock = IsKeyEventModifierSet(modifier, KeyEvent::Modifier::CapsLock);

        char toInsert{0};
        if (IsKeyCodeAlpha(keycode))
        {
            char alpha = KeyCodeToAlpha(keycode);
            toInsert = ((capsLock && !shift) || (!capsLock && shift)) ? alpha : static_cast<char>(std::tolower(alpha));
        }
        else if (IsKeyCodeDigit(keycode))
            toInsert = KeyCodeToGraph(keycode);
        else if (IsKeyCodeSpace(keycode))
            toInsert = ' ';

        if (toInsert != 0)
        {
            std::string str{getText()};
            str.insert(m_cursorLocation , 1, toInsert);
            moveCursor(1, str.size());
            setText(str);
        }
    }

    void TextField::removeFromText(int direction)
    {
        if (direction > 0)
        {
            if (m_cursorLocation < getText().size())
            {
                std::string str{getText()};
                str.erase(m_cursorLocation, 1);
                setText(str);
            }
        }
        else
        {
            if (m_cursorLocation > 0)
            {
                std::string str{getText()};
                str.erase(m_cursorLocation - 1, 1);
                moveCursor(-1, str.size());
                setText(str);
            }
        }
    }

    void TextField::moveCursor(int direction, std::size_t strSize, bool shouldDraw)
    {
        if (direction > 0)
        {
            if (m_cursorLocation < strSize)
            {
                ++m_cursorLocation;
                if (shouldDraw)
                    draw();
            }
        }
        else
        {
            if (m_cursorLocation > 0)
            {
                --m_cursorLocation;
                if (shouldDraw)
                    draw();
            }
        }
    }

    void TextField::moveCursorToPos(std::size_t pos, std::size_t strSize, bool shouldDraw)
    {
        if ((m_cursorLocation != pos) && (pos <= strSize))
        {
            m_cursorLocation = pos;
            if (shouldDraw)
                draw();
        }
    }

    void TextField::onDraw(SkCanvas* canvas)
    {
        Rectangle::onDraw(canvas);
        PTK_INFO("CURSOR LOCATION: {}", m_cursorLocation);
        const Size rectSize{getSize()};
        
        float advance = (!getText().empty()) ? drawTextLine(canvas, getText(), m_textColor, m_textPos) : 0.0f;
        
        if (getText().empty())
            drawTextLine(canvas, m_placeholderText, m_placeholderColor, m_textPos);

        if (m_drawCursor)
        {
            SkPaint paint{GetSkPaintFromColor(m_textColor)};
            paint.setStrokeWidth(1.0f);

            if (m_cursorLocation <= getText().size())
            {
                SkRect tmp{};
                advance = skFont()->measureText(getText().c_str(), m_cursorLocation, SkTextEncoding::kUTF8, &tmp);
            }

            float posX = m_textPos.x + advance - ((m_cursorLocation == 0) ? 2.0f : 0.0f);

            float startY = static_cast<float>(getPosition().y)  + ((static_cast<float>(rectSize.height) - m_cursorHeight) / 2);
            float endY = startY + m_cursorHeight;
            canvas->drawLine({posX, startY}, {posX, endY}, paint);
        }
    }

    void TextField::onTextUpdate()
    {
        updateBounds();
    }

    void TextField::setPosHint(const Point& pos)
    {
        Widget::setPosHint(pos);
        updateBounds();
    }

    void TextField::updateBounds()
    {
        const float capitalHeight{capHeight()};
        const Size rectSize{getSize()};
        const Point pos{getPosition()};

        float fHeight{static_cast<float>(rectSize.height)};
        float center{(fHeight - capitalHeight) / 2};
        m_textPos.x = static_cast<float>(pos.x) + center;
        m_textPos.y = static_cast<float>(pos.y) + center;
        
        m_cursorHeight = ascentToDescent();
        
        Size minSize{getBounds()};
        minSize.width += 1;
        auto ceilCursorHeight = static_cast<Point::value_type>(std::ceil(m_cursorHeight));
        minSize.height = (minSize.height > ceilCursorHeight) ? minSize.height : ceilCursorHeight;
        
        SkRect placeholderBounds{};
        skFont()->measureText(m_placeholderText.c_str(), m_placeholderText.size(), SkTextEncoding::kUTF8, &placeholderBounds);
        auto pWidth = static_cast<Size::value_type>(std::ceil(placeholderBounds.width()));
        auto pHeight = static_cast<Size::value_type>(std::ceil(placeholderBounds.height()));
        
        minSize.width = (minSize.width > pWidth) ? minSize.width : pWidth;
        minSize.height = (minSize.height > pHeight) ? minSize.height : pHeight;
        
        setMinSize(minSize);
        update();
    }

    void TextField::setPlaceholderText(const std::string& text)
    {
        m_placeholderText = text;
        updateBounds();
    }

    const std::string& TextField::getPlaceholderText() const
    {
        return m_placeholderText;
    }

    void TextField::setPlaceholderColor(const Color& color)
    {
        m_placeholderColor = color;
        update();
    }

    const Color& TextField::getPlaceholderColor() const
    {
        return m_placeholderColor;
    }

    void TextField::setTextColor(const Color& color)
    {
        m_textColor = color;
        update();
    }

    const Color& TextField::getTextColor() const
    {
        return m_textColor;
    }
}
