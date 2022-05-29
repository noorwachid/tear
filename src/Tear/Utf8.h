#pragma once

#include <string>

namespace Tear::Utf8 {
	uint8_t getCodepointByteSize(char firstByte);
	uint8_t getCodepointByteMask(uint8_t byteSize);
	uint8_t getCodepointWidth(uint32_t codepoint);

	uint32_t toCodepoint(const std::string& bytes, size_t byteOffset = 0);

	std::string toString(uint32_t codepoint);
}
