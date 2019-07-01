//
//  widgets/Label.cpp
//  pTK
//
//  Created by Robin Gustafsson on 2019-06-30.
//

// Local Headers
#include "ptk/widgets/Label.hpp"
#include "ptk/Log.hpp"

// Skia Headers
#include "include/core/SkFont.h"
#include "include/core/SkTypeface.h"
#include "include/core/SkPaint.h"
#include "include/core/SkTextBlob.h"

#include <stdexcept>
#include <iostream>

namespace pTK
{
    Label::Label()
        : Shape(), m_fontName{""}, m_fontSize{12}, m_text{}
    {
        
    }
    
    void Label::setFont(const std::string& font)
    {
        m_fontName = font;
        calculateBounds();
    }
    
    void Label::setFontSize(uint fontSize)
    {
        m_fontSize = fontSize;
        calculateBounds();
    }
    
    void Label::setText(const std::string& text)
    {
        m_text = text;
        calculateBounds();
    }
    
    void Label::calculateBounds()
    {
        // Font
        SkFont font;
        if (m_fontName == "")
            font = SkFont(SkTypeface::MakeDefault(), m_fontSize);
        else
         font = SkFont(SkTypeface::MakeFromName(m_fontName.c_str(), SkFontStyle::Normal()), m_fontSize);
        
        SkRect bounds;
        font.measureText(m_text.c_str(), m_text.size(), SkTextEncoding::kUTF8, &bounds);
        setSizeHint(Size(bounds.width(), bounds.height()));
    }
    
    void Label::onDraw(const Canvas& canvas)
    {
        SkCanvas* skCanvas = canvas.skCanvas();
        Vec2f dpiScale{canvas.getDPIScale()};
        
        // Set Color.
        SkPaint paint;
        paint.setAntiAlias(true);
        Color color = getColor();
        paint.setARGB(color.a, color.r, color.g, color.b);
        
        SkFont font;
        if (m_fontName == "")
            font = SkFont(SkTypeface::MakeDefault(), m_fontSize);
        else
            font = SkFont(SkTypeface::MakeFromName(m_fontName.c_str(), SkFontStyle::Normal()), m_fontSize*dpiScale.x);
        
        // Calculate Bounds and Position.
        SkRect bounds;
        font.measureText(m_text.c_str(), m_text.size(), SkTextEncoding::kUTF8, &bounds);
        SkPoint pos{convertToSkPoint(getPosition(), dpiScale)};
        
        // Outline
        float outlineThickness = getOutlineThickness();
        paint.setStrokeWidth(outlineThickness*dpiScale.x);
        if (outlineThickness > 0.0f)
        {
            float halfOutlineThickness = outlineThickness/2;
            pos.fX += halfOutlineThickness*dpiScale.x;
            pos.fY += halfOutlineThickness*dpiScale.y;
            paint.setStyle(SkPaint::kFill_Style);
        }else
        {
            paint.setStyle(SkPaint::kStrokeAndFill_Style);
        }
        
        skCanvas->drawString(m_text.c_str(), pos.fX + (-1*bounds.x()), pos.fY + (-1*bounds.y()), font, paint);
        
        if (outlineThickness > 0.0f)
        {
            // Draw Outline
            Color outColor = getOutlineColor();
            paint.setARGB(outColor.a, outColor.r, outColor.g, outColor.b);
            paint.setStyle(SkPaint::kStroke_Style);
            skCanvas->drawString(m_text.c_str(), pos.fX + (-1*bounds.x()), pos.fY + (-1*bounds.y()), font, paint);
        }
    }
}
