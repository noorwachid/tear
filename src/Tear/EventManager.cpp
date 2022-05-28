#include "EventManager.h"
#include <vector>
#include <sys/select.h>
#include <unistd.h>

namespace Tear {
	int EventManager::inputDescriptor;

	std::string EventManager::inputBuffer;

	fd_set descriptors;
	int timeoutMS = 1000; // A second

	void EventManager::initialize(int inputDescriptor) {
		EventManager::inputDescriptor = inputDescriptor;
		EventManager::inputBuffer += "[" + std::to_string(inputDescriptor) + "]";
	}

	void EventManager::emit(const Event& event) {
	}

	void EventManager::poll() {
		struct timeval timeout;
		timeout.tv_sec = timeoutMS / 1000;
		timeout.tv_usec = (timeoutMS - (timeout.tv_sec * 1000)) * 1000;

		FD_ZERO(&descriptors);
		FD_SET(inputDescriptor, &descriptors);

		bool active = ::select(inputDescriptor + 1, &descriptors, 0, 0, &timeout);
		if (!active) {
			return;
		}

		while (true) {
			if (FD_ISSET(inputDescriptor, &descriptors) && pollInput()) {
				return;
			}

			// TODO: implement on window resized
		}
	}

	bool EventManager::pollInput() {
		ssize_t readSize = 0;
		ssize_t targetSize = 64;
		std::vector<char> temporaryBuffer(targetSize, '\0');

		ssize_t currentSize = ::read(
			inputDescriptor,
			temporaryBuffer.data() + readSize,
			temporaryBuffer.size() - readSize
		);

		inputBuffer += std::string(temporaryBuffer.data(), readSize);

		return readSize >= 0;
	}

}
