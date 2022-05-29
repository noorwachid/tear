#pragma once 

#include "Event.h"

namespace Tear::EventManager {
	using EventListener = std::function<void (Event&)>;

	void emit(Event& event);
	void subscribe(const std::string& type, const EventListener& listener);
}
