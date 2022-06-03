#include "EventManager.h"
#include "Term.h"

namespace Tear 
{
	void EventManager::Emit(Event& event) 
	{
		// avoid [] operator because it's alocate on demand
		if (listenerMap.count(event.type)) 
		{
			std::vector<EventListener>& listeners = listenerMap[event.type];
			
			for (EventListener& listener: listeners) 
			{
				listener(event);
			}
		}
	}

	void EventManager::Subscribe(const std::string& type, const EventListener& listener) 
	{
		listenerMap[type].push_back(listener);
	}
}
