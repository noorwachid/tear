#pragma once

#include <array>
#include <vector>

namespace Tear {
    struct Pixel {
        uint32_t codepoint = ' ';

        Pixel() = default;
        Pixel(int newCodepoint): codepoint(newCodepoint) {
        }
    };

	using FrameDescriptor = std::array<int, 2>;

	class Frame {
	public:
        Frame();
        ~Frame();

        bool isOpen() { return open; }
		int getWidth() const { return width; }  
		int getHeight() const { return height; }
		const FrameDescriptor& getDescriptor() const { return descriptor; }


	private:
        bool open = false;
		int width = 0;
		int height = 0;
		FrameDescriptor descriptor;
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
}
