#pragma once

#include "Cell.h"
#include "Sequence.h"

namespace Tear {
	class Renderer {
	public:
		static void initialize(int descriptor, const OutputSequence& sequence);

		static void submit(const std::string& buffer);

		static void clear();

		static void showCursor();

		static void hideCursor();

		static void setCursor(int x, int y);

		static void setStyle(Style style);

		static void setForeground(Color color);

		static void setBackground(Color background);

		static void reset();

	private:
		static int descriptor;

		static OutputSequence sequence;
	};
}
