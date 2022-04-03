#pragma once

#include <string>
#include <cstdint>

namespace Tear {
    enum class Key: uint16_t {
        backspace = 0x08,
        tab = 0x09,
        enter = 0x0D,
        escape = 0x1B,
        space = 0x20,
        delete_ = 0x7f,

        zero = 0x30,
        one,
        two,
        three,
        four,
        five,
        six,
        seven,
        eight,
        nine,

        a = 0x61,
        b,
        c,
        d,
        e,
        f,
        g,
        h,
        i,
        j,
        k,
        l,
        m,
        n,
        o,
        p,
        q,
        r,
        s,
        t,
        u,
        v,
        w,
        x,
        y,
        z,

        f1 = 0x81,
        f2,
        f3,
        f4,
        f5,
        f6,
        f7,
        f8,
        f9,
        f10,
        f11,
        f12,

        backtick,
        minus,
        equal,

        leftBracket,
        rightBracket,
        backslash,

        semicolon,
        quote,

        comma,
        dot,
        slash,

        insert,
        home,
        end,
        pageUp,
        pageDown,

        up,
        down,
        left,
        right,
    };

    enum class ModifierKey: uint8_t {
        none = 0x0,
        shift = 0x1,
        control = 0x2,
        alternate = 0x4,
    };

    std::string toString(Key key);

    std::string toString(ModifierKey modifierKey);
}
