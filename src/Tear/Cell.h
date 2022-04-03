#pragma once

#include "Utf8.h"
#include <vector>

namespace Tear {
	using Color = uint8_t;

	enum class Style {
		bold,
		italic,
		underlined,
	};

	struct Cell {
		CodePoint codePoint;
		Color foreground;
		Color background;
		Style style;
	};

	struct CellBuffer {
		size_t width;
		size_t height;

		std::vector<Cell> data;

		void set(int x, int y, const Cell& cell) {
			data[y * width + x] = cell;
		}

		Cell& get(int x, int y) {
			return data[y * width + x];
		}
	};
}
