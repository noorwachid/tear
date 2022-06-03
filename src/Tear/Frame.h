#pragma once

#include <array>
#include <vector>

namespace Tear 
{
    struct Pixel 
    {
        uint32_t codepoint = ' ';

        Pixel() = default;
        Pixel(int newCodepoint): codepoint(newCodepoint) {}
    };

	using FrameDescriptor = std::array<int, 2>;

	class Frame 
    {
	public:
        Frame();
        ~Frame();

        bool IsOpen() { return open; }
		int GetWidth() const { return width; }  
		int GetHeight() const { return height; }
		const FrameDescriptor& GetDescriptor() const { return descriptor; }


	private:
        bool open = false;
		int width = 0;
		int height = 0;
		FrameDescriptor descriptor;
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
}
