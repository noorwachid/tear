#include "Renderer.h"
#include "Term.h"
#include "Utf8.h"

namespace Tear
{
    void FrameBuffer::Recreate(int newWidth, int newHeight) 
    {
        width = newWidth;
        height = newHeight;
        pixels.resize(width * height);
    }

    void FrameBuffer::Set(int x, int y, const Pixel& cell) 
    {
        pixels[y * width + x] = cell;
    }

    const Pixel& FrameBuffer::Get(int x, int y) const 
    {
        return pixels[y * width + x];
    }

    Pixel& FrameBuffer::Get(int x, int y) 
    {
        return pixels[y * width + x];
    }

    namespace Renderer 
    {
        struct RendererData 
        {
            FrameBuffer front;
            FrameBuffer back;

            std::string outputSequence;
        };

        static RendererData data;
        
        void Initialize() 
        {
            size_t width = Term::GetWidth();
            size_t height = Term::GetHeight();

            data.front.Recreate(width, height);
            data.back.Recreate(width, height);
        }

        void Set(int x, int y, uint32_t codepoint) 
        {
            data.back.Set(x, y, Pixel(codepoint));
        }

        void Set(int x, int y, const std::string& text) 
        {
            for (size_t textIndex = 0, codepointIndex = 0; textIndex < text.size();) 
            {
                uint32_t codepoint = Utf8::ToCodepoint(text, textIndex);
                int codepointWidth = Utf8::GetCodepointWidth(codepoint);

                data.back.Set(x + codepointIndex, y, codepoint);

                for (int i = 1; i < codepointWidth; ++i) 
                {
                    data.back.Set(x + codepointIndex + i, y, ' ');
                }

                textIndex += Utf8::GetCodepointByteSize(text[textIndex]);
                codepointIndex += codepointWidth;
            }
        }

        void Flush() 
        {
            data.outputSequence.clear();

            for (int y = 0; y < data.back.height; ++y) 
            {
                for (int x = 0; x < data.back.width; ++x) 
                {
                    Pixel& frontPixel = data.front.Get(x, y);
                    Pixel& backPixel = data.back.Get(x, y);

                    if (frontPixel.codepoint != backPixel.codepoint) 
                    {
                        data.outputSequence += Term::GetSequence().command.Move(x, y);
                        data.outputSequence += Utf8::ToString(backPixel.codepoint);

                        frontPixel = backPixel;
                    }
                }
            }

            Term::Write(data.outputSequence);
        }
    }
}