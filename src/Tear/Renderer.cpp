#include "Renderer.h"
#include "Utf8.h"

namespace Tear {        
    Renderer::Renderer(const std::shared_ptr<Sequence>& newSequence, int width, int height) {
        sequence = newSequence;
        recreate(width, height);
    }

    void Renderer::recreate(int width, int height) {
        front.recreate(width, height);
        back.recreate(width, height);
    }

    void Renderer::set(int x, int y, uint32_t codepoint) {
        back.set(x, y, Pixel(codepoint));
    }

    void Renderer::set(int x, int y, const std::string& text) {
        for (size_t textIndex = 0, codepointIndex = 0; textIndex < text.size();) {
            uint32_t codepoint = Utf8::toCodepoint(text, textIndex);
            int codepointWidth = Utf8::getCodepointWidth(codepoint);

            back.set(x + codepointIndex, y, codepoint);

            for (int i = 1; i < codepointWidth; ++i) {
                back.set(x + codepointIndex + i, y, ' ');
            }

            textIndex += Utf8::getCodepointByteSize(text[textIndex]);
            codepointIndex += codepointWidth;
        }
    }

    void Renderer::swapBuffers() {
        buffer.clear();

        for (int y = 0; y < back.height; ++y) {
            for (int x = 0; x < back.width; ++x) {
                Pixel& frontPixel = front.get(x, y);
                Pixel& backPixel = back.get(x, y);

                if (frontPixel.codepoint != backPixel.codepoint) {
                    buffer += sequence->command.move(x, y);
                    buffer += Utf8::toString(backPixel.codepoint);

                    frontPixel = backPixel;
                }
            }
        }
    }
}