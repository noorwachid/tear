#include "EventManager.h"
#include "Term.h"

namespace Tear {
	void EventManager::emit(Event& event) {
		// avoid [] operator because it's alocate on demand
		if (listenerMap.count(event.type)) {
			std::vector<EventListener>& listeners = listenerMap[event.type];
			for (EventListener& listener: listeners) {
				listener(event);
			}
		}
	}

	void EventManager::subscribe(const std::string& type, const EventListener& listener) {
		listenerMap[type].push_back(listener);
	}
}
