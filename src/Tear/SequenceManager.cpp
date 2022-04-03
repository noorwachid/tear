#include "SequenceManager.h"

#include <sys/select.h>
#include <sys/stat.h>
#include <termios.h>
#include <unistd.h>

namespace Tear {
	SequenceManager::SequenceManager(const std::string& term) {
		data = nullptr;

		if (term.empty()) {
			return;
		}

		this->term = term;

		const char* terminfoPath = ::getenv("TERMINFO");
		if (terminfoPath && readFolder(terminfoPath)) {
			return;
		}

		const char* homePath = ::getenv("HOME");
		if (homePath && readFolder(std::string(homePath) + "/.terminfo")) {
			return;
		}

		readFolder("/usr/share/terminfo");
	}

	SequenceManager::~SequenceManager() {
		if (data) {
			delete[] data;
			data = nullptr;
		}
	}

	bool SequenceManager::readFile(const std::string& path) {
		FILE *file = ::fopen(path.c_str(), "rb");
		if (!file) {
			return false;
		}

		struct stat fileStat;
		if (::fstat(::fileno(file), &fileStat) != 0) {
			::fclose(file);

			return false;
		}

		data = new char[fileStat.st_size];
		if (fread(data, 1, fileStat.st_size, file) != (size_t) fileStat.st_size) {
			delete[] data;
			data = nullptr;
			::fclose(file);

			return false;
		}

		::fclose(file);
		calculateOffsets();

		return true;
	}

	bool SequenceManager::readFolder(const std::string& prefixPath) {
		char tmp[4096];

		// GNU/Linux
		snprintf(tmp, sizeof(tmp), "%s/%c/%s", prefixPath.c_str(), term[0], term.c_str());
		tmp[sizeof(tmp)-1] = '\0';

		if (readFile(tmp)) {
			return true;
		}

		// MacOS
		snprintf(tmp, sizeof(tmp), "%s/%x/%s", prefixPath.c_str(), term[0], term.c_str());
		tmp[sizeof(tmp)-1] = '\0';

		if (readFile(tmp)) {
			return true;
		}

		return false;
	}

	char* SequenceManager::duplicate(int str, int table) {
		const int16_t off = *(int16_t*) (data + str);
		const char *src = data + table + off;
		int len = strlen(src);
		char *dst = new char[len + 1];
		strcpy(dst, src);
		
		return dst;
	}

	void SequenceManager::calculateOffsets() {
		alternateSlice = 542;
		headerSize = 12;
		header = (int16_t*) data;
		numSecSize = header[0] == alternateSlice ? 4 : 2;

		if ((header[1] + header[2]) % 2) {
			// old quirk to align everything on word boundaries
			header[2] += 1;
		}

		stringOffset = headerSize + header[1] + header[2] + numSecSize * header[3];
		tableOffset = stringOffset + 2 * header[4];
	}

	bool SequenceManager::exists() {
		return data;
	}

	Sequence SequenceManager::compose() {
		Sequence sequence;

		const int16_t commandOffsets[] = {
			28, 40, 16, 13, 5, 39, 36, 27, 26, 34, 89, 88,
		};

		sequence.caListener = duplicate(stringOffset + 2 * commandOffsets[0], tableOffset);
		sequence.caExit = duplicate(stringOffset + 2 * commandOffsets[1], tableOffset);
		sequence.keypadListener = duplicate(stringOffset + 2 * commandOffsets[10], tableOffset);
		sequence.keypadExit = duplicate(stringOffset + 2 * commandOffsets[11], tableOffset);
		sequence.mouseListener = "\x1b[?1000h\x1b[?1002h\x1b[?1015h\x1b[?1006h";
		sequence.mouseExit = "\x1b[?1006l\x1b[?1015l\x1b[?1002l\x1b[?1000l";

		return sequence;
	}

	OutputSequence SequenceManager::composeOutput() {
		OutputSequence sequence;

		const int16_t commandOffsets[] = {
			28, 40, 16, 13, 5, 39, 36, 27, 26, 34, 89, 88,
		};

		sequence.cursorShown = duplicate(stringOffset + 2 * commandOffsets[2], tableOffset);
		sequence.cursorHidden = duplicate(stringOffset + 2 * commandOffsets[3], tableOffset);
		sequence.clear = duplicate(stringOffset + 2 * commandOffsets[4], tableOffset);
		sequence.sgr0 = duplicate(stringOffset + 2 * commandOffsets[5], tableOffset);
		sequence.underlined = duplicate(stringOffset + 2 * commandOffsets[6], tableOffset);
		sequence.bold = duplicate(stringOffset + 2 * commandOffsets[7], tableOffset);
		sequence.blink = duplicate(stringOffset + 2 * commandOffsets[8], tableOffset);
		sequence.reverse = duplicate(stringOffset + 2 * commandOffsets[9], tableOffset);

		return sequence;
	}

	InputSequence SequenceManager::composeInput() {
		InputSequence sequence;

		const int16_t keyOffsets[] = {
			66, 68 , 69, 70, 
			71, 72, 73, 74, 
			75, 67, 216, 217, 

			77, 59, 
			76, 164, 
			82, 81, 

			87, 61, 79, 83,
		};

		for (size_t i = 0; i < sequence.keys.size(); ++i) {
			sequence.keys[i] = duplicate(stringOffset + 2 * keyOffsets[i], tableOffset);
		}

		return sequence;
	}
}
