#pragma once

#include "Sequence.h"
#include <vector>

namespace Tear {
    struct Pixel {
        uint32_t codepoint = ' ';

        Pixel() = default;
        Pixel(int newCodepoint): codepoint(newCodepoint) {
        }
    };

    struct FrameBuffer {
        std::vector<Pixel> pixels;

        void recreate(int newWidth, int newHeight);
        void set(int x, int y, const Pixel& cell);

        const Pixel& get(int x, int y) const;
        Pixel& get(int x, int y);

        int width;
        int height;
    };

    namespace Renderer {
        void initialize();
        void set(int x, int y, uint32_t codepoint);
        void set(int x, int y, const std::string& text);
        void swapBuffers();
    }
}