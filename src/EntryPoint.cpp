#include "Tear/Session.h"
#include "Tear/EventManager.h"
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <iostream>

using namespace Tear;

struct Pixel {
	uint32_t codepoint = ' ';

	Pixel() = default;
	Pixel(int newCodepoint): codepoint(newCodepoint) {
	}
};

struct Buffer {
	std::vector<Pixel> pixels;

	void recreate(int newWidth, int newHeight) {
		width = newWidth;
		height = newHeight;
		pixels.resize(width * height);
	}

	void set(int x, int y, const Pixel& cell) {
		pixels[y * width + x] = cell;
	}

	const Pixel& get(int x, int y) const {
		return pixels[y * width + x];
	}

	Pixel& get(int x, int y) {
		return pixels[y * width + x];
	}

	size_t width;
	size_t height;
};

class Renderer {
public:
	Renderer(int newIODescriptor, const Sequence& newSequence, int width, int height) {
		ioDescriptor = newIODescriptor;
		sequence = newSequence;

		frontBuffer.recreate(width, height);
		backBuffer.recreate(width, height);
	}

	void set(int x, int y, uint32_t codepoint) {
		backBuffer.set(x, y, Pixel(codepoint));
	}

	void set(int x, int y, const std::string& text) {
		for (size_t textIndex = 0, codepointIndex = 0; textIndex < text.size();) {
			uint32_t codepoint = Utf8::toCodepoint(text, textIndex);
			int codepointWidth = Utf8::getCodepointWidth(codepoint);

			backBuffer.set(x + codepointIndex, y, codepoint);

			for (int i = 1; i < codepointWidth; ++i) {
				backBuffer.set(x + codepointIndex + i, y, ' ');
			}

			textIndex += Utf8::getCodepointByteSize(text[textIndex]);
			codepointIndex += codepointWidth;
		}
	}

	void flush() {
		outputData.clear();

		for (int y = 0; y < backBuffer.height; ++y) {
			for (int x = 0; x < backBuffer.width; ++x) {
				Pixel& frontPixel = frontBuffer.get(x, y);
				Pixel& backPixel = backBuffer.get(x, y);

				if (frontPixel.codepoint != backPixel.codepoint) {
					outputData += sequence.command.move(x, y);
					outputData += Utf8::toString(backPixel.codepoint);

					frontPixel = backPixel;
				}
			}
		}

		::write(ioDescriptor, outputData.data(), outputData.size());
	}

private:
	int ioDescriptor;
	Sequence sequence;

	Buffer frontBuffer;
	Buffer backBuffer;

	std::string outputData;
};

int main() {
	// std::string emoji = "😀";
	// uint32_t codepoint = Utf8::toCodepoint(emoji);

	// std::cout << codepoint << "\n";
	// std::cout << 0x10000 << " " << 0x10FFFF << "\n";

	// std::cout << int(Utf8::getCodepointWidth(codepoint)) << "\n";

	Session session;
	Renderer renderer(session.ioDescriptor, session.sequence, 100, 80);

	int frameCount = 0;

	session.write(session.sequence.command.clear);
	
	while (session.isOpen() && frameCount < 10000) {
		++frameCount;

		renderer.set(0, 0, "😀:" + std::to_string(frameCount));
		renderer.flush();
	}
}
