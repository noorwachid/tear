#pragma once

#include "Key.h"
#include "Mouse.h"
#include <string>

namespace Tear 
{
    struct Event 
    {
        std::string type;

        Event() = default;
        Event(const std::string& type): type(type) {}
    };

    struct KeyEvent: public Event 
    {
        uint32_t codePoint;
        Key key;
        ModifierKey modifierKey;
    };

    struct MouseEvent: public Event 
    {
        int x;
        int y;
        bool moving;
        MouseButton button;
        int direction;
    };

    struct FrameEvent: public Event 
    {
        int width;
        int height;
    };
}
