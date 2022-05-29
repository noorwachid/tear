#include "Core.h"
#include "Renderer.h"
#include "Utf8.h"

namespace Tear {
    void FrameBuffer::recreate(int newWidth, int newHeight) {
        width = newWidth;
        height = newHeight;
        pixels.resize(width * height);
    }

    void FrameBuffer::set(int x, int y, const Pixel& cell) {
        pixels[y * width + x] = cell;
    }

    const Pixel& FrameBuffer::get(int x, int y) const {
        return pixels[y * width + x];
    }

    Pixel& FrameBuffer::get(int x, int y) {
        return pixels[y * width + x];
    }

    namespace Renderer {
        struct RendererData {
            FrameBuffer front;
            FrameBuffer back;

            std::string outputBuffer;
        };

        static RendererData data;
        
        void initialize() {
            size_t width = getFrameWidth();
            size_t height = getFrameHeight();

            data.front.recreate(width, height);
            data.back.recreate(width, height);
        }

        void set(int x, int y, uint32_t codepoint) {
            data.back.set(x, y, Pixel(codepoint));
        }

        void set(int x, int y, const std::string& text) {
            for (size_t textIndex = 0, codepointIndex = 0; textIndex < text.size();) {
                uint32_t codepoint = Utf8::toCodepoint(text, textIndex);
                int codepointWidth = Utf8::getCodepointWidth(codepoint);

                data.back.set(x + codepointIndex, y, codepoint);

                for (int i = 1; i < codepointWidth; ++i) {
                    data.back.set(x + codepointIndex + i, y, ' ');
                }

                textIndex += Utf8::getCodepointByteSize(text[textIndex]);
                codepointIndex += codepointWidth;
            }
        }

        void swapBuffers() {
            data.outputBuffer.clear();

            for (int y = 0; y < data.back.height; ++y) {
                for (int x = 0; x < data.back.width; ++x) {
                    Pixel& frontPixel = data.front.get(x, y);
                    Pixel& backPixel = data.back.get(x, y);

                    if (frontPixel.codepoint != backPixel.codepoint) {
                        data.outputBuffer += getSequence().command.move(x, y);
                        data.outputBuffer += Utf8::toString(backPixel.codepoint);

                        frontPixel = backPixel;
                    }
                }
            }

            write(data.outputBuffer);
        }

        const std::string& GetOutputBuffer() {
            return data.outputBuffer;
        }
    }
}