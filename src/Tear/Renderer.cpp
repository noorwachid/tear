#include "Renderer.h"
#include "Utf8.h"

namespace Tear 
{        
    Renderer::Renderer(const std::shared_ptr<Sequence>& newSequence, int width, int height) 
    {
        sequence = newSequence;
        Recreate(width, height);
    }

    void Renderer::Recreate(int width, int height) 
    {
        front.Recreate(width, height);
        back.Recreate(width, height);
    }

    void Renderer::Set(int x, int y, uint32_t codepoint) 
    {
        back.Set(x, y, Pixel(codepoint));
    }

    void Renderer::Set(int x, int y, const std::string& text) 
    {
        for (size_t textIndex = 0, codepointIndex = 0; textIndex < text.size();) 
        {
            uint32_t codepoint = Utf8::ToCodepoint(text, textIndex);
            int codepointWidth = Utf8::GetCodepointWidth(codepoint);

            back.Set(x + codepointIndex, y, codepoint);

            for (int i = 1; i < codepointWidth; ++i) 
            {
                back.Set(x + codepointIndex + i, y, ' ');
            }

            textIndex += Utf8::GetCodepointByteSize(text[textIndex]);
            codepointIndex += codepointWidth;
        }
    }

    void Renderer::SwapBuffers() 
    {
        buffer.clear();

        for (int y = 0; y < back.height; ++y) 
        {
            for (int x = 0; x < back.width; ++x) 
            {
                Pixel& frontPixel = front.Get(x, y);
                Pixel& backPixel = back.Get(x, y);

                if (frontPixel.codepoint != backPixel.codepoint) 
                {
                    buffer += sequence->command.Move(x, y);
                    buffer += Utf8::ToString(backPixel.codepoint);

                    frontPixel = backPixel;
                }
            }
        }
    }
}