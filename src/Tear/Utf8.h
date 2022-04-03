#pragma once

#include <string>

namespace Tear {
	using CodePoint = uint32_t;

	struct Utf8 {
		static uint8_t getCodePointByteSize(char firstByte);
		static uint8_t getCodePointByteMask(uint8_t byteSize);

		static CodePoint toCodePoint(const std::string& bytes);

		static std::string toString(CodePoint codePoint);
	};
}
