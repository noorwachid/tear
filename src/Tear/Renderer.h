#pragma once

#include "Sequence.h"
#include <vector>

namespace Tear
{
    struct Pixel 
    {
        uint32_t codepoint = ' ';

        Pixel() = default;
        Pixel(int newCodepoint): codepoint(newCodepoint) 
        {
        }
    };

    struct FrameBuffer 
    {
        std::vector<Pixel> pixels;

        void Recreate(int newWidth, int newHeight);
        void Set(int x, int y, const Pixel& cell);

        const Pixel& Get(int x, int y) const;
        Pixel& Get(int x, int y);

        int width;
        int height;
    };

    namespace Renderer 
    {
        void Initialize();
        void Set(int x, int y, uint32_t codepoint);
        void Set(int x, int y, const std::string& text);
        void Flush();
    }
}