#pragma once

#include "Sequence.h"

namespace Tear {
	class SequenceDatabase {
	public:
		SequenceDatabase(const std::string& termName);
		~SequenceDatabase();

		bool exists();

		ModeSequence composeMode();
		CommandSequence composeCommand();
		KeySequence composeKey();

	private:
		bool readFolder(const std::string& path);
		bool readFile(const std::string& path);

		char* duplicate(int str, int table);

		void calculateOffsets();

	private:
		char* data;
		
		std::string termName;

		int alternateSlice = 542;
		int headerSize = 12;
		int16_t* header;

		int numSecSize;
		int stringOffset;
		int tableOffset;
	};
}
