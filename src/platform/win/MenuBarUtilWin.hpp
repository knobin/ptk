//
//  platform/win/MenuBarUtilWin.hpp
//  pTK
//
//  Created by Robin Gustafsson on 2021-01-16.
//

// TODO(knobin): Add docs for all functions in file.

#ifndef PTK_PlATFORM_WIN_MENUBARUTIL_HPP
#define PTK_PlATFORM_WIN_MENUBARUTIL_HPP

// pTK Headers
#include "ptk/events/KeyCodes.hpp"
#include "ptk/menu/Menu.hpp"
#include "ptk/menu/MenuItem.hpp"
#include "ptk/menu/Shortcut.hpp"

// C++ Headers
#include <map>
#include <optional>
#include <vector>

// Windows Headers
#define NOMINMAX
#include <windows.h>

namespace pTK::Platform::MenuBarUtilWin
{
    using MenuMap = std::map<uint32_t, std::tuple<std::shared_ptr<MenuItem>, uint32_t, bool, HMENU>>;

    void CreateMenuStructure(HMENU parent, MenuMap& menus, const std::shared_ptr<pTK::Menu>& menu, uint32_t parentId,
                             std::vector<ACCEL>& keys);
    uint32_t InsertMenuItemToMap(MenuMap& menus, const std::shared_ptr<MenuItem>& menuItem, uint32_t parentId,
                                 bool isMenu, HMENU hmenu);
    std::shared_ptr<MenuItem> FindMenuItemById(const MenuMap& menuItems, uint32_t id);
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

} // namespace pTK::Platform::MenuBarUtilWin

#endif // PTK_PlATFORM_WIN_MENUBARUTIL_HPP