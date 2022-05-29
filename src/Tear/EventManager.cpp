#include "EventManager.h"
#include "Term.h"
#include <vector>
#include <unordered_map>
#include <functional>

namespace Tear::EventManager {
	struct EventManagerData {
		std::unordered_map<std::string, std::vector<EventListener>> listeners;
	};

	static EventManagerData data;

	void Emit(Event& event) {
		// avoid [] operator because it's alocate on demand
		if (data.listeners.count(event.type)) {
			std::vector<EventListener>& listeners = data.listeners[event.type];
			for (EventListener& listener: listeners) {
				listener(event);
			}
		}
	}

	void Subscribe(const std::string& type, const EventListener& listener) {
		data.listeners[type].push_back(listener);
	}
}
