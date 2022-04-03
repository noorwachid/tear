#include "Renderer.h"
#include <unistd.h>

namespace Tear {
	int Renderer::descriptor = 0;

	OutputSequence Renderer::sequence;

	void Renderer::initialize(int descriptor, const OutputSequence& sequence) {
		Renderer::descriptor = descriptor;
		Renderer::sequence = sequence;
	}

	void Renderer::submit(const std::string& buffer) {
		::write(descriptor, buffer.data(), buffer.size());
	}

	void Renderer::clear() {
		submit(sequence.clear);
	}

	void Renderer::showCursor() {
		submit(sequence.cursorShown);
	}

	void Renderer::hideCursor() {
		submit(sequence.cursorHidden);
	}

	void Renderer::setCursor(int x, int y) {
		submit("\033[" + std::to_string(y + 1) + ";" + std::to_string(x + 1) + "H");
	}

	void Renderer::setStyle(Style style) {
	}

	void Renderer::setForeground(Color color) {
	}

	void Renderer::setBackground(Color color) {
	}

	void Renderer::reset() {
		submit(sequence.sgr0);
	}

}
