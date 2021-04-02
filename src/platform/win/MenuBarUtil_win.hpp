//
//  platform/win/MenuBarUtil_win.hpp
//  pTK
//
//  Created by Robin Gustafsson on 2021-01-16.
//

#ifndef PTK_PlATFORM_WIN_MENUBARUTIL_HPP
#define PTK_PlATFORM_WIN_MENUBARUTIL_HPP

// pTK Headers
#include "ptk/events/KeyCodes.hpp"
#include "ptk/menu/MenuItem.hpp"
#include "ptk/menu/Menu.hpp"
#include "ptk/menu/Shortcut.hpp"

// C++ Headers
#include <map>
#include <optional>
#include <vector>

namespace pTK::MenuBarUtil_win
{
    using MenuMap = std::map<uint, std::tuple<Ref<MenuItem>, uint, bool, HMENU>>;

    void CreateMenuStructure(HMENU parent, MenuMap& menus, const pTK::Ref<pTK::Menu>& menu, uint parentId, std::vector<ACCEL>& keys);
    uint InsertMenuItemToMap(MenuMap& menus, const Ref<MenuItem>& menuItem, uint parentId, bool isMenu, HMENU hmenu);
    Ref<MenuItem> FindMenuItemById(const MenuMap& menuItems, uint id);
    std::string TranslateKeyCodeToShortcutStr(const KeyCode& key);
    std::optional<std::pair<ACCEL, std::string>> GetShortcutACCEL(const Shortcut& shortcut);
    std::string TranslateKeyCodesToShortcutStr(const Shortcut& shortcut);

    static constexpr UINT MenuItemStatusToFlag(const MenuItemStatus& status) noexcept
    {
        UINT flag = 0;
        switch (status)
        {
            case MenuItemStatus::Enabled:
                flag |= MF_ENABLED;
                break;
            case MenuItemStatus::Disabled:
                flag |= MF_DISABLED | MF_GRAYED;
                break;
            case MenuItemStatus::Checked:
                flag |= MF_CHECKED;
                break;
            case MenuItemStatus::Unchecked:
                flag |= MF_UNCHECKED;
                break;
        }
        return flag;
    }

} // namespace pTK

#endif // PTK_PlATFORM_WIN_MENUBARUTIL_HPP