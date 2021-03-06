#include "Utf8.h"

// NOTE: No offense, if you are JS or Python programmers just skip reading this file

namespace Tear::Utf8 
{	
	// Using look-up to minimize branches in the code
	static uint8_t byteSizeMap[256] = 
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 1, 1
	};

	static uint8_t byteMaskMap[7] = 
	{
		0xff, // Ignored index to avoid calculation of -1, because you know SPEED

		0x7f,
		0x1f,
		0x0f,
		0x07,
		0x03,
		0x01,
	};

	uint8_t GetCodepointByteSize(char firstByte) 
	{
		return byteSizeMap[(uint8_t) firstByte];
	}

	uint8_t GetCodepointByteMask(uint8_t byteSize) 
	{
		return byteMaskMap[byteSize];
	}

	uint8_t GetCodepointWidth(uint32_t codepoint) 
	{
		return (codepoint >= 0x10000 && codepoint <= 0x10FFFF) + 1;
	}

	uint32_t ToCodepoint(const std::string& bytes, size_t byteOffset) 
	{
		// TODO: Do something to remove the if statement
		if (bytes[byteOffset] == 0x0) 
		{
			return -1; // 0xffff_ffff
		}

		uint8_t size = GetCodepointByteSize(bytes[byteOffset]);
		uint8_t mask = GetCodepointByteMask(size);

		uint32_t codepoint = bytes[byteOffset] & mask;

		for (uint8_t i = byteOffset + 1; i < size; ++i) 
		{
			codepoint <<= 6;
			codepoint |= bytes[i] & 0x3f;
		}

		return codepoint;
	}

	std::string ToString(uint32_t codepoint) 
	{
		uint8_t mask;
		uint8_t size = 0;

		if (codepoint < 0x80) 
		{
			mask = 0;
			size = 1;
		} 
		else if (codepoint < 0x800) 
		{
			mask = 0xc0;
			size = 2;
		} 
		else if (codepoint < 0x10000) 
		{
			mask = 0xe0;
			size = 3;
		} 
		else if (codepoint < 0x200000) 
		{
			mask = 0xf0;
			size = 4;
		} 
		else if (codepoint < 0x4000000) 
		{
			mask = 0xf8;
			size = 5;
		} 
		else 
		{
			mask = 0xfc;
			size = 6;
		}

		std::string bytes(size, 0x0); 

		for (uint8_t i = size - 1; i > 0; --i) 
		{
			bytes[i] = (codepoint & 0x3f) | 0x80;
			codepoint >>= 6;
		}

		bytes[0] = codepoint | mask;

		return bytes;
	}
}
