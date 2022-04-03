#include "Utf8.h"

// NOTE: No offense, if you are JS or Python programmers just skip reading this file

namespace Tear {
	
	// Using look-up to minimize branches in the code
	static uint8_t byteSizeMap[256] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 1, 1
	};

	static uint8_t byteMaskMap[7] = {
		0xff, // Ignored index to avoid calculation of -1, because you know SPEED

		0x7f,
		0x1f,
		0x0f,
		0x07,
		0x03,
		0x01,
	};

	uint8_t Utf8::getCodePointByteSize(char firstByte) {
		return byteSizeMap[(uint8_t) firstByte];
	}

	uint8_t Utf8::getCodePointByteMask(uint8_t byteSize) {
		return byteMaskMap[byteSize];
	}

	CodePoint Utf8::toCodePoint(const std::string& bytes) {
		// TODO: Do something to remove the if statement
		if (bytes[0] == 0x0) {
			return -1; // 0xffff_ffff
		}

		uint8_t size = getCodePointByteSize(bytes[0]);
		uint8_t mask = getCodePointByteMask(size);

		CodePoint codePoint = bytes[0] & mask;

		for (uint8_t i = 1; i < size; ++i) {
			codePoint <<= 6;
			codePoint |= bytes[i] & 0x3f;
		}

		return codePoint;
	}

	std::string Utf8::toString(CodePoint codePoint) {
		uint8_t mask;
		uint8_t size = 0;

		if (codePoint < 0x80) {
			mask = 0;
			size = 1;
		} else if (codePoint < 0x800) {
			mask = 0xc0;
			size = 2;
		} else if (codePoint < 0x10000) {
			mask = 0xe0;
			size = 3;
		} else if (codePoint < 0x200000) {
			mask = 0xf0;
			size = 4;
		} else if (codePoint < 0x4000000) {
			mask = 0xf8;
			size = 5;
		} else {
			mask = 0xfc;
			size = 6;
		}

		std::string bytes(size, 0x0); 

		for (uint8_t i = size - 1; i > 0; --i) {
			bytes[i] = (codePoint & 0x3f) | 0x80;
			codePoint >>= 6;
		}

		bytes[0] = codePoint | mask;

		return bytes;
	}
}
