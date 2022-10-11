//
//  core/WidgetContainer.hpp
//  pTK
//
//  Created by Robin Gustafsson on 2019-11-18.
//

#ifndef PTK_CORE_WIDGETCONTAINER_HPP
#define PTK_CORE_WIDGETCONTAINER_HPP

// pTK Headers
#include "ptk/core/Widget.hpp"

// C++ Headers
#include <stdexcept>
#include <utility>
#include <vector>

namespace pTK
{
    /** WidgetContainer class implementation.

        Derived from Container, this class for holding Widgets in
        order of displaying them.
    */
    class PTK_API WidgetContainer : public Widget
    {
    public:
        using value_type = Ref<Widget>;
        using reference = value_type&;
        using const_reference = const value_type&;
        using container_type = std::vector<value_type>;
        using iterator = container_type::iterator;
        using reverse_iterator = container_type::reverse_iterator;
        using const_iterator = container_type::const_iterator;
        using const_reverse_iterator = container_type::const_reverse_iterator;
        using size_type = std::size_t;

    public:
        /** Constructs WidgetContainer with default values.

            @return    default initialized WidgetContainer
        */
        WidgetContainer();

        /** Move Constructor for WidgetContainer.

            @return    initialized WidgetContainer from value
        */
        WidgetContainer(WidgetContainer&& other) = default;

        /** Move Assignment operator for WidgetContainer.

            @return    WidgetContainer with value
        */
        WidgetContainer& operator=(WidgetContainer&& other) = default;

        /** Destructor for WidgetContainer.

        */
        virtual ~WidgetContainer();

        // TODO(knobin): Add docs.
        void add(const Ref<Widget>& widget);

        // TODO(knobin): Add docs.
        void remove(const Ref<Widget>& widget);

        /** Function for setting the position of the VBox and its children.

            @param pos     Position to set
        */
        void setPosHint(const Point& pos) override;

        /** Function is called when it is time to draw.

            @param canvas  canvas to draw to
        */
        void onDraw(SkCanvas* canvas) override;

        /** Function for a child Widget to call the Parent when it need to be drawn.

            @param widget  Child Widget
            @return        Status (true if handled)
        */
        bool updateChild(Widget* widget) override;

        /** Function for a child Widget to call the Parent when it need to be drawn.

            @param widget  Child Widget
            @return        Status (true if handled)
        */
        bool drawChild(Widget* widget) override;

        /** Function for setting the background of the Container.

            @param color   background color
        */
        void setBackground(const Color& color);

        /** Function for getting the background of the Container.

            @return    current background color
        */
        [[nodiscard]] const Color& getBackground() const;

        // TODO(knobin): Add docs.
        [[nodiscard]] Widget* getSelectedWidget() const;

        /** Function for retrieving the an iterator that points to the first
            value in the WidgetContainer.

            The iterator may be equal to end iterator if the WidgetContainer is empty.

            @return    iterator
        */
        [[nodiscard]] iterator begin() noexcept { return m_holder.begin(); }

        /** Function for retrieving the an iterator that points to the first
            value in the WidgetContainer.

            The iterator may be equal to end iterator if the WidgetContainer is empty.

            @return    const iterator
        */
        [[nodiscard]] const_iterator begin() const noexcept { return m_holder.begin(); }

        /** Function for retrieving the an const iterator that points to the first
            value in the WidgetContainer.

            The iterator may be equal to end iterator if the WidgetContainer is empty.

            @return    const iterator
        */
        [[nodiscard]] const_iterator cbegin() const noexcept { return m_holder.cbegin(); }

        /** Function for retrieving the special iterator referring to
            the past-the-end of the WidgetContainer.

            The iterator should never be de-referenced, due to the fact that the iterator
            does not point to a value and should therefore only be used for checking.

            @return    iterator
        */
        [[nodiscard]] iterator end() noexcept { return m_holder.end(); }

        /** Function for retrieving the special iterator referring to
            the past-the-end of the WidgetContainer.

            The iterator should never be de-referenced, due to the fact that the iterator
            does not point to a value and should therefore only be used for checking.

            @return    const iterator
        */
        [[nodiscard]] const_iterator end() const noexcept { return m_holder.end(); }

        /** Function for retrieving the special const iterator referring to
            the past-the-end of the WidgetContainer.

            The iterator should never be dereferenced, due to the fact that the iterator
            does not point to a value and should therefore only be used for checking.

            @return    const iterator
        */
        [[nodiscard]] const_iterator cend() const noexcept { return m_holder.cend(); }

        /** Function for retrieving the an iterator that points to the last
            value in the WidgetContainer.

            This iterator is working in reverse. Meaning that is starts at the end
            and is moving to the beginning.

            The iterator may be equal to rend iterator if the WidgetContainer is empty.

            @return    reverse iterator
        */
        [[nodiscard]] reverse_iterator rbegin() noexcept { return m_holder.rbegin(); }

        /** Function for retrieving the an iterator that points to the last
            value in the WidgetContainer.

            This iterator is working in reverse. Meaning that is starts at the end
            and is moving to the beginning.

            The iterator may be equal to rend iterator if the WidgetContainer is empty.

            @return    const reverse begin iterator
        */
        [[nodiscard]] const_reverse_iterator rbegin() const noexcept { return m_holder.rbegin(); }

        /** Function for retrieving the an iterator that points to the last
            value in the WidgetContainer.

            This iterator is working in reverse. Meaning that is starts at the end
            and is moving to the beginning.

            The iterator may be equal to rend iterator if the WidgetContainer is empty.

            @return    const reverse begin iterator
        */
        [[nodiscard]] const_reverse_iterator crbegin() const noexcept { return m_holder.crbegin(); }

        /** Function for retrieving the special const iterator referring to
            the past-the-end of the WidgetContainer.

            The iterator should never be de-referenced, due to the fact that the iterator
            does not point to a value and should therefore only be used for checking.

            @return    reverse reverse end iterator
        */
        [[nodiscard]] reverse_iterator rend() noexcept { return m_holder.rend(); }

        /** Function for retrieving the special const iterator referring to
            the past-the-end of the WidgetContainer.

            The iterator should never be de-referenced, due to the fact that the iterator
            does not point to a value and should therefore only be used for checking.

            @return    const reverse end iterator
        */
        [[nodiscard]] const_reverse_iterator rend() const noexcept { return m_holder.rend(); }

        /** Function for retrieving the special const iterator referring to
             the past-the-end of the WidgetContainer.

             The iterator should never be de-referenced, due to the fact that the iterator
             does not point to a value and should therefore only be used for checking.

             @return    const reverse end iterator
         */
        [[nodiscard]] const_reverse_iterator crend() const noexcept { return m_holder.crend(); }

        /** Function for retrieving the element at the index in the WidgetContainer.
            @param pos      Index
            @return         element in WidgetContainer
        */
        [[nodiscard]] reference at(size_type pos)
        {
            if (pos >= m_holder.size())
                throw std::out_of_range("Index is out of range!");

            return m_holder[pos];
        }

        /** Function for retrieving the element at the index in the WidgetContainer.
            @param pos      Index
            @return         element in WidgetContainer
        */
        [[nodiscard]] const_reference at(size_type pos) const
        {
            if (pos >= m_holder.size())
                throw std::out_of_range("Position is out of range!");

            return m_holder[pos];
        }

        /** Function for retrieving the first element in the WidgetContainer.
            Should in no circumstances be called when the WidgetContainer is empty!
            This is considered to be undefined behavior!
            @return    first element in WidgetContainer
        */
        [[nodiscard]] reference front() noexcept { return m_holder.front(); }

        /** Function for retrieving the first element in the WidgetContainer.
            Should in no circumstances be called when the WidgetContainer is empty!
            This is considered to be undefined behavior!
            @return    first element in WidgetContainer
        */
        [[nodiscard]] const_reference front() const noexcept { return m_holder.front(); }

        /** Function for retrieving the last element in the WidgetContainer.
            Should in no circumstances be called when the WidgetContainer is empty!
            This is considered to be undefined behavior!
            @return    last element in WidgetContainer
        */
        [[nodiscard]] reference back() noexcept { return m_holder.back(); }

        /** Function for retrieving the last element in the WidgetContainer.
            Should in no circumstances be called when the WidgetContainer is empty!
            This is considered to be undefined behavior!
            @return    last element in WidgetContainer
        */
        [[nodiscard]] const_reference back() const noexcept { return m_holder.back(); }

        /** Function for retrieving the current amount of items in the WidgetContainer.

            @return     number of items in container
        */
        [[nodiscard]] size_type count() const noexcept { return m_holder.size(); }

    protected:
        /** Function for checking if a child has called a parent function.

            Used to avoid unnecessary recursion.
            If this function will break something in the future (might do), replace it.

            @return     status
        */
        [[nodiscard]] bool busy() const;

        // TODO(knobin): Add docs.
        void drawBackground(SkCanvas* canvas) const;

        // TODO(knobin): Add docs.
        void drawChildren(SkCanvas* canvas)
        {
            for (auto it = m_holder.begin(); it != m_holder.end(); ++it)
                (*it)->onDraw(canvas);
        }

    private:
        void initCallbacks();

        /** Callback to use when a Widget has been successfully added.

            @param widget   child that has been added
        */
        virtual void onAdd(const Ref<Widget>& UNUSED(widget)) {}

        /** Callback to use when a Widget has been removed.

            Note: widget has already been removed from the container and cannot be accessed with
            any non-modifying functions.

            @param widget   child that has been removed
        */
        virtual void onRemove(const Ref<Widget>& UNUSED(widget)) {}

        /** Callback to use when a child has called the parent update function.

            @param index   the index of the child
        */
        virtual void onChildUpdate(size_type UNUSED(index)) {}

        /** Callback to use when a child has called the parent draw function.

            @param index   the index of the child
        */
        virtual void onChildDraw(size_type UNUSED(index)) {}

    private:
        /** Function for handling when a key is pressed or released.

            @param type     Key event (press or release)
            @param KeyCode  Keycode
        */
        void onKeyCallback(const KeyEvent& evt);

        /** Function for handling key input.

            @param data         array of display characters
            @param size         amount of characters
            @param encoding     encoding of the characer data
        */
        void onInputCallback(const InputEvent& evt);

        /** Function for handling when mouse is hovering.

            @param pos     position
        */
        void onHoverCallback(const MotionEvent& evt);

        /** Function for handling when mouse is entering.

        */
        void onEnterCallback(const EnterEvent& evt);

        /** Function for handling when mouse is leaving.

        */
        void onLeaveCallback(const LeaveEvent& evt);

        /** Function for handling when mouse is scrolling.

            @param offset     x and y offset
        */
        void onScrollCallback(const ScrollEvent& evt);

        /** Function for handling when mouse is clicking.

            @param button      which button on mouse triggered the event.
            @param position    x and y position
        */
        void onClickCallback(const ClickEvent& evt);

        /** Function for handling when mouse is released.

            Derived from EventFunctions.

            @param button      which button on mouse triggered the event.
            @param position    x and y position
        */
        void onReleaseCallback(const ReleaseEvent& evt);

    private:
        // Variables
        container_type m_holder{};
        Color m_background{0xf5f5f5ff};
        Widget* m_lastClickedWidget{nullptr};
        Widget* m_currentHoverWidget{nullptr};
        bool m_busy{false};
    };

} // namespace pTK

#endif // PTK_CORE_WIDGETCONTAINER_HPP
