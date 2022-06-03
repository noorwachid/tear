#pragma once

#include "Sequence.h"

namespace Tear 
{
	class SequenceDatabase 
	{
	public:
		SequenceDatabase(const std::string& termName);
		~SequenceDatabase();

		std::shared_ptr<Sequence> get();

	private:
		ModeSequence ComposeMode();
		CommandSequence ComposeCommand();
		KeySequence ComposeKey();

		bool ReadFolder(const std::string& path);
		bool ReadFile(const std::string& path);

		char* Duplicate(int str, int table);

		void CalculateOffsets();

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
