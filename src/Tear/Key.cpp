#include "Key.h"

namespace Tear {
    std::string toString(Key key) {
        switch (key) {
            case Key::backspace: return "Backspace";
            case Key::tab: return "Tab";
            case Key::enter: return "Enter";
            case Key::escape: return "Escape";
            case Key::space: return "Space";
            case Key::delete_: return "Delete";

            case Key::zero: return "Zero";
            case Key::one: return "One";
            case Key::two: return "Two";
            case Key::three: return "Three";
            case Key::four: return "Four";
            case Key::five: return "Five";
            case Key::six: return "Six";
            case Key::seven: return "Seven";
            case Key::eight: return "Eight";
            case Key::nine: return "Nine";

            case Key::a: return "A";
            case Key::b: return "B";
            case Key::c: return "C";
            case Key::d: return "D";
            case Key::e: return "E";
            case Key::f: return "F";
            case Key::g: return "G";
            case Key::h: return "H";
            case Key::i: return "I";
            case Key::j: return "J";
            case Key::k: return "K";
            case Key::l: return "L";
            case Key::m: return "M";
            case Key::n: return "N";
            case Key::o: return "O";
            case Key::p: return "P";
            case Key::q: return "Q";
            case Key::r: return "R";
            case Key::s: return "S";
            case Key::t: return "T";
            case Key::u: return "U";
            case Key::v: return "V";
            case Key::w: return "W";
            case Key::x: return "X";
            case Key::y: return "Y";
            case Key::z: return "Z";

            case Key::f1: return "F1";
            case Key::f2: return "F2";
            case Key::f3: return "F3";
            case Key::f4: return "F4";
            case Key::f5: return "F5";
            case Key::f6: return "F6";
            case Key::f7: return "F7";
            case Key::f8: return "F8";
            case Key::f9: return "F9";
            case Key::f10: return "F10";
            case Key::f11: return "F11";
            case Key::f12: return "F12";

            case Key::backtick: return "Backtick";
            case Key::minus: return "Minus";
            case Key::equal: return "Equal";

            case Key::leftBracket: return "LeftBracket";
            case Key::rightBracket: return "RightBracket";
            case Key::backslash: return "Backslash";

            case Key::semicolon: return "Semicolon";
            case Key::quote: return "Quote";

            case Key::comma: return "Comma";
            case Key::dot: return "Dot";
            case Key::slash: return "Slash";

            case Key::insert: return "Insert";
            case Key::home: return "Home";
            case Key::end: return "End";
            case Key::pageUp: return "PageUp";
            case Key::pageDown: return "PageDown";

            case Key::up: return "Up";
            case Key::down: return "Down";
            case Key::left: return "Left";
            case Key::right: return "Right";

            default: return "-";
        }
    }

    std::string toString(ModifierKey modifierKey) {
        switch (modifierKey) {
            case ModifierKey::shift: return "Shift";
            case ModifierKey::control: return "Control";
            case ModifierKey::alternate: return "Alternate";
            default: return "-";
        }
    }
}
