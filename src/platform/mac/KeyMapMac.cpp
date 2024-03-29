//
//  src/platform/mac/KeyMapMac.cpp
//  pTK
//
//  Created by Robin Gustafsson on 2021-01-19.
//

// pTK Headers
#include "ptk/events/KeyCodes.hpp"

// C++ Headers
#include <map>

namespace pTK::Platform::KeyMapFactoryImpl
{
    std::map<int32_t, KeyCode> Make()
    {
        std::map<int32_t, KeyCode> map{};

        // clang-format off
        
        map[0x31] = Key::Space;
        map[0x1D] = Key::D0; map[0x12] = Key::D1; map[0x13] = Key::D2; map[0x14] = Key::D3;
        map[0x15] = Key::D4; map[0x17] = Key::D5; map[0x16] = Key::D6; map[0x1A] = Key::D7;
        map[0x1C] = Key::D8; map[0x19] = Key::D9;
        map[0x52] = Key::D0; map[0x53] = Key::D1; map[0x54] = Key::D2; map[0x55] = Key::D3;
        map[0x56] = Key::D4; map[0x57] = Key::D5; map[0x58] = Key::D6; map[0x59] = Key::D7;
        map[0x5B] = Key::D8; map[0x5C] = Key::D9;
        map[0x00] = Key::A; map[0x0B] = Key::B; map[0x08] = Key::C; map[0x02] = Key::D;
        map[0x0E] = Key::E; map[0x03] = Key::F; map[0x05] = Key::G; map[0x04] = Key::H;
        map[0x22] = Key::I; map[0x26] = Key::J; map[0x28] = Key::K; map[0x25] = Key::L;
        map[0x2E] = Key::M; map[0x2D] = Key::N; map[0x1F] = Key::O; map[0x23] = Key::P;
        map[0x0C] = Key::Q; map[0x0F] = Key::R; map[0x01] = Key::S; map[0x11] = Key::T;
        map[0x20] = Key::U; map[0x09] = Key::V; map[0x0D] = Key::W; map[0x07] = Key::X;
        map[0x10] = Key::Y; map[0x06] = Key::Z;

        map[0x35] = Key::Escape; map[0x24] = Key::Enter; map[0x30] = Key::Tab;
        map[0x33] = Key::Backspace; map[0x75] = Key::Delete;

        map[0x7C] = Key::Right; map[0x7B] = Key::Left;
        map[0x7D] = Key::Down; map[0x7E] = Key::Up;

        map[0x38] = Key::LeftShift; map[0x3B] = Key::LeftControl;
        map[0x3A] = Key::LeftAlt; map[0x37] = Key::LeftSuper;

        map[0x3C] = Key::LeftShift; map[0x3E] = Key::LeftControl;
        map[0x3D] = Key::LeftAlt; map[0x36] = Key::LeftSuper;

        // clang-format on

        return map;
    }

} // namespace pTK::Platform::KeyMapFactoryImpl
