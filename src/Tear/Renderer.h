#pragma once

#include "Frame.h"
#include "Sequence.h"
#include <vector>

namespace Tear 
{
    class Renderer 
    {
    public:
        Renderer(const std::shared_ptr<Sequence>& sequence, int width, int height);

        void Recreate(int width, int height);
        void Set(int x, int y, uint32_t codepoint);
        void Set(int x, int y, const std::string& text);
        void SwapBuffers();

        const std::string& GetBuffer() const { return buffer; }

    private:
        FrameBuffer front;
        FrameBuffer back;
        std::shared_ptr<Sequence> sequence;
        std::string buffer;
    };
}