#pragma once

#include "Event.h"
#include <vector>

namespace Tear {
	class Node {
	public:
		virtual void onCreate();

		virtual void onDestroy();

		virtual void onUpdate();
		
		virtual void onEvent(Event& event);

	protected:
		std::vector<Node*> children;
	};
}
