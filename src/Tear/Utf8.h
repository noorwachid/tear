#pragma once

#include <string>

namespace Tear 
{
	struct Utf8 
	{
		static uint8_t GetCodepointByteSize(char firstByte);
		static uint8_t getCodepointByteMask(uint8_t byteSize);
		static uint8_t GetCodepointWidth(uint32_t codepoint);

		static uint32_t ToCodepoint(const std::string& bytes, size_t byteOffset = 0);

		static std::string ToString(uint32_t codepoint);
	};
}
