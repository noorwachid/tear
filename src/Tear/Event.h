#pragma once

#include "Key.h"
#include "Mouse.h"
#include "Utf8.h"

namespace Tear {
    enum class EventType {
        keyPressed,

        mouseButtonPressed,
        mouseButtonReleased,
        mouseWheelScrolled,

        windowResized,
    };

    struct Event {
        EventType type;
    };

    struct KeyEvent: public Event {
        uint32_t codePoint;
        Key key;
        ModifierKey modifierKey;
    };

    struct MouseEvent: public Event {
        int x;
        int y;
        bool moving;
    };

    struct MouseButtonEvent: public MouseEvent {
        MouseButton button;
    };

    struct MouseWheelEvent: public MouseEvent {
        int direction;
    };

    struct WindowEvent: public Event {
        int x;
        int y;
    };
}
