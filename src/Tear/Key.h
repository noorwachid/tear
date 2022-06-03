#pragma once

#include <string>
#include <cstdint>

namespace Tear 
{
    enum class Key: uint16_t 
    {
        Backspace = 0x08,
        Tab = 0x09,
        Return = 0x0D,
        Escape = 0x1B,
        Space = 0x20,
        Delete = 0x7f,

        Zero = 0x30,
        One,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,

        A = 0x61,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,

        F1 = 0x81,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,

        Backtick,
        Minus,
        Equal,

        LeftBracket,
        RightBracket,
        Backslash,

        Semicolon,
        Quote,

        Comma,
        Dot,
        Slash,

        Insert,
        Home,
        End,
        PageUp,
        PageDown,

        Up,
        Down,
        Left,
        Right,
    };

    enum class ModifierKey: uint8_t 
    {
        None = 0x0,
        Shift = 0x1,
        Control = 0x2,
        Alternate = 0x4,
    };

    std::string toString(Key key);
    std::string toString(ModifierKey modifierKey);
}
