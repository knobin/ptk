//
//  events/KeyCodes.hpp
//  pTK
//
//  Created by Robin Gustafsson on 2020-04-19.
//

#ifndef PTK_KEYCODES_HPP
#define PTK_KEYCODES_HPP

// C++ Header
#include <cstdint>

// TODO: Add more keycodes.

namespace pTK
{
    // clang-format off

    typedef enum class KeyCode : int32_t
    {
        Unknown = 0,
        Space   = 32,

        // Numbers
        D0      = 48,
        D1      = 49,
        D2      = 50,
        D3      = 51,
        D4      = 52,
        D5      = 53,
        D6      = 54,
        D7      = 55,
        D8      = 56,
        D9      = 57,

        // Letters
        A       = 65,
        B       = 66,
        C       = 67,
        D       = 68,
        E       = 69,
        F       = 70,
        G       = 71,
        H       = 72,
        I       = 73,
        J       = 74,
        K       = 75,
        L       = 76,
        M       = 77,
        N       = 78,
        O       = 79,
        P       = 80,
        Q       = 81,
        R       = 82,
        S       = 83,
        T       = 84,
        U       = 85,
        V       = 86,
        W       = 87,
        X       = 88,
        Y       = 89,
        Z       = 90,

        Escape      = 256,
        Enter       = 257,
        Tab         = 258,
        Backspace   = 259,
        Delete      = 261,

        Right   = 262,
        Left    = 263,
        Down    = 264,
        Up      = 265,

        Home    = 268,
        End     = 269,

        LeftShift    = 340,
        LeftControl  = 341,
        LeftAlt      = 342,
        LeftSuper    = 343,

        RightShift   = 344,
        RightControl = 345,
        RightAlt     = 346,
        RightSuper   = 347,

        // Shift   = 348,
        // Control = 349,
        // Alt     = 350,
        // Command = 351

    } Key;

    // clang-format on

    constexpr bool IsKeyCodeAlpha(const KeyCode code) noexcept
    {
        const auto value = static_cast<int32_t>(code);
        return ((value >= 65) && (value <= 90));
    }

    constexpr char KeyCodeToAlpha(const KeyCode code) noexcept
    {
        return static_cast<char>(static_cast<int32_t>(code));
    }

    constexpr bool IsKeyCodeDigit(const KeyCode code) noexcept
    {
        const auto value = static_cast<int32_t>(code);
        return ((value >= 48) && (value <= 57));
    }

    constexpr uint8_t KeyCodeToDigit(const KeyCode code) noexcept
    {
        constexpr auto zero = static_cast<uint8_t>(Key::D0);
        return static_cast<uint8_t>(static_cast<int32_t>(code) - zero);
    }

    constexpr bool IsKeyCodeModifier(const KeyCode code) noexcept
    {
        const auto value = static_cast<int32_t>(code);
        return ((value >= 340) && (value <= 351));
    }

    constexpr bool IsKeyCodeGraph(const KeyCode code) noexcept
    {
        // A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
        // 0 1 2 3 4 5 6 7 8 9
        return (IsKeyCodeAlpha(code) || IsKeyCodeDigit(code));

        // Lowercase is not supported yet: a b c d e f g h i j k l m n o p q r s t u v w x y z
        // TODO: Add values below.
        // ! " # $ % & ' ( ) * + , - . /
        // : ; < = > ? @
        // [ \ ] ^ _ `
        // { | } ~
    }

    constexpr char KeyCodeToGraph(const KeyCode code) noexcept
    {
        if (IsKeyCodeAlpha(code))
            return KeyCodeToAlpha(code);
        if (IsKeyCodeDigit(code))
            return static_cast<char>(static_cast<int32_t>(code));
        return 0;
    }

    constexpr bool IsKeyCodeSpace(const KeyCode code) noexcept
    {
        return code == Key::Space;
    }
} // namespace pTK

#endif // PTK_KEYCODES_HPP
