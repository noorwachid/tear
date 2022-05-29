#pragma once

#include "Sequence.h"
#include "Event.h"

namespace Tear {
	void initialize();
	void terminate();
	void terminateWithError(const std::string& message);

	void close();
	bool isOpen();

	void write(const std::string& buffer);
	std::string read(size_t chuck = 64);

	int getFrameWidth();
	int getFrameHeight();

	int getIODescriptor();

	const std::string& getTerm();
	const Sequence& getSequence();

}
