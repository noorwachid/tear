#pragma once

#include "Sequence.h"

namespace Tear::Term
{
	void Initialize();
	void Terminate();
	void TerminateWithError(const std::string& message);

	void RestorePreviousState();
	void SavePreviousState();

	void Close();
	bool IsOpen();

	void Write(const std::string& buffer);

	int GetWidth();
	int GetHeight();
	int GetIODescriptor();

	const std::string& GetName();
	const Sequence& GetSequence();
}
