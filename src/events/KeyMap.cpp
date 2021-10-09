//
//  events/KeyMap.cpp
//  pTK
//
//  Created by Robin Gustafsson on 2021-01-18.
//

// Local Headers
#include "ptk/platform/PlatformInit.hpp"

// pTK Headers
#include "ptk/events/KeyMap.hpp"

// C++ Headers
#include <map>

namespace pTK
{
    KeyMap KeyMap::s_Instance{};

    KeyMap::KeyMap()
        : SingleObject(), m_keyMap{KeyMapInit()}
    {

    }

    KeyMap& KeyMap::Get()
    {
        return s_Instance;
    }

    const std::map<int32, Key>& KeyMap::Map()
    {
        return Get().m_keyMap;
    }

    bool KeyMap::KeyExists(Key key)
    {
        const std::map<int32, Key>& keyMap{Get().m_keyMap};
        auto it = std::find_if(keyMap.cbegin(), keyMap.cend(), [&](const auto& pair){
            return pair.second == key;
        });

        return it != keyMap.cend();
    }

    Key KeyMap::KeyCodeToKey(int32 code)
    {
        const std::map<int32, Key>& keyMap{Get().m_keyMap};
        std::map<int32, KeyCode>::const_iterator it{keyMap.find(code)};
        if (it != keyMap.cend())
            return it->second;

        return Key::Unknown;
    }

    int32 KeyMap::KeyToKeyCode(Key key)
    {
        const std::map<int32, Key>& keyMap{Get().m_keyMap};
        auto it = std::find_if(keyMap.cbegin(), keyMap.cend(), [&](const auto& pair){
            return pair.second == key;
        });

        if (it != keyMap.cend())
            return it->first;

        return static_cast<int32>(Key::Unknown);
    }

} // namespace pTK
