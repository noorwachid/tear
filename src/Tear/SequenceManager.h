#pragma once

#include "Sequence.h"

namespace Tear {
	class SequenceManager {
	public:
		SequenceManager(const std::string& term);

		~SequenceManager();

		bool exists();

		Sequence compose();

		OutputSequence composeOutput();

		InputSequence composeInput();

	private:
		bool readFolder(const std::string& path);

		bool readFile(const std::string& path);

		char* duplicate(int str, int table);

		void calculateOffsets();

		char* data;

		std::string term;

	private:
		int alternateSlice = 542;
		int headerSize = 12;
		int16_t* header;

		int numSecSize;
		int stringOffset;
		int tableOffset;
	};
}
