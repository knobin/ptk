//
//  widgets/HBox.hpp
//  pTK
//
//  Created by Robin Gustafsson on 2019-11-27.
//

#ifndef PTK_WIDGETS_HBOX_HPP
#define PTK_WIDGETS_HBOX_HPP

// Local Headers
#include "ptk/core/Box.hpp"

// C++ Headers
#include <utility>

namespace pTK
{
    /** HBox class implementation.
     
        Derived from Box, this class for holding Cells in
        order of displaying them in a vertical style.
    */
    class HBox : public Box
    {
    public:
        /** Constructs HBox with default values.
         
            @return    default initialized HBox
        */
        HBox();

        /** Deconstructor for HBox.

        */
        virtual ~HBox() = default;
        
    protected:
        void refitContent(const Size& size);

    private:
        void onAdd(const Ref<Widget>&) override;
        void onRemove(const Ref<Widget>&) override;
        void onChildUpdate(size_type) override;
        void onResize(const Size& size) override;
        
    private:
        void expandOnAdd(const Size& newSize);
        Size calcMinSize() const;
        Size calcMaxSize() const;
        
        std::vector<Size::value_type> calcSpaces(Size::value_type width);
        Point::value_type alignChildV(size_type index, const Size& parentSize, const Size& childSize);
    };
}

#endif // PTK_WIDGETS_HBOX_HPP
