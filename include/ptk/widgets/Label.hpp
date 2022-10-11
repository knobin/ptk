//
//  widgets/Label.hpp
//  pTK
//
//  Created by Robin Gustafsson on 2019-06-30.
//

#ifndef PTK_WIDGETS_LABEL_HPP
#define PTK_WIDGETS_LABEL_HPP

// pTK Headers
#include "ptk/core/Shape.hpp"
#include "ptk/core/Text.hpp"

namespace pTK
{
    /** Label class implementation.

        This class is for drawing a Label.
        Deriving from Shape instead of directly of Widget,
        is for the unique properties that Shape has that Label
        can also use. Such as Color and outline.
    */
    class PTK_API Label : public Shape, public Text
    {
    public:
        /** Constructs Label with default values.

            @return    default initialized Label
        */
        Label();

        /** Move Constructor for Label.

            @return    initialized Label from value
        */
        Label(Label&& other) = default;

        /** Move Assignment operator for Label.

            @return    Label with value
        */
        Label& operator=(Label&& other) = default;

        /** Move Constructor for Label.

            @return    initialized Label from value
        */
        virtual ~Label() = default;

        /** Draw function.
            Function is called when it is time to draw.

            Derived from Drawable.
        */
        void onDraw(SkCanvas* canvas) override;

        void setText(const std::string& str);
        const std::string& getText() const;

    private:
        // Label should only change size on setFontSize!
        using Widget::setMaxSize;
        using Widget::setMinSize;
        using Widget::setSize;

        void onTextUpdate() override;

        // Only supports UTF-8 for now.
        std::string m_text{};
    };
} // namespace pTK

#endif // PTK_WIDGETS_LABEL_HPP
