#pragma once

#include "Key.h"
#include "Mouse.h"
#include "Utf8.h"

namespace Tear 
{
    enum class EventType 
	{
        KeyPressed,
        MousePressed,
        MouseScrolled,
        FrameBufferResized,
    };

    struct Event 
	{
        EventType type;
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

    struct FrameBufferEvent: public Event 
	{
        int width;
        int height;
    };
}
