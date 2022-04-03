#pragma once 

#include "Event.h"
#include <string>

namespace Tear {
	class EventManager {
	public:
		static void initialize(int inputDescriptor);

		static void emit(const Event& event);

		static void poll();

	private:
		static bool pollInput();
	
	private:
		static int inputDescriptor;

	public:
		static std::string inputBuffer;
	};
}
