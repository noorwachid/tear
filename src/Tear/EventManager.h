#pragma once 

#include "Event.h"
#include <vector>
#include <unordered_map>
#include <functional>

namespace Tear {
	using EventListener = std::function<void (Event&)>;
	
	class EventManager {
	public:
		void emit(Event& event);
		void subscribe(const std::string& type, const EventListener& listener);

	private:
		std::unordered_map<std::string, std::vector<EventListener>> listenerMap;
	};
}
