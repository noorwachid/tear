#pragma once

#include <string>

namespace Tear::Utf8 
{
	uint8_t GetCodepointByteSize(char firstByte);
	uint8_t GetCodepointByteMask(uint8_t byteSize);
	uint8_t GetCodepointWidth(uint32_t codepoint);

	uint32_t ToCodepoint(const std::string& bytes, size_t byteOffset = 0);

	std::string ToString(uint32_t codepoint);
}
