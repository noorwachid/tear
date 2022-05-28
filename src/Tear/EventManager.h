#pragma once 

#include "Event.h"
#include <string>

namespace Tear::EventManager 
{
	void Initialize();
	void Emit(const Event& event);
	void Poll();
	bool PollInput();

	const std::string& GetInputSequence();
}
