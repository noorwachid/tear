#pragma once

#include <string>

namespace Tear {
	struct Utf8 {
		static uint8_t getCodepointByteSize(char firstByte);
		static uint8_t getCodepointByteMask(uint8_t byteSize);
		static uint8_t getCodepointWidth(uint32_t codepoint);

		static uint32_t toCodepoint(const std::string& bytes, size_t byteOffset = 0);

		static std::string toString(uint32_t codepoint);
	};
}
