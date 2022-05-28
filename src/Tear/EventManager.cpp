#include "EventManager.h"
#include "Term.h"
#include <vector>
#include <sys/select.h>
#include <unistd.h>

namespace Tear::EventManager
{
	struct EventManagerData
	{
		int inputDescriptor;
		std::string inputSequence;
		fd_set descriptors;
		int timeoutMS = 1000; // A second
	};

	static EventManagerData data;


	void Initialize() 
	{
		data.inputDescriptor = Term::GetIODescriptor();
	}

	void Emit(const Event& event) 
	{
	}

	void Poll() 
	{
		struct timeval timeout;
		timeout.tv_sec = data.timeoutMS / 1000;
		timeout.tv_usec = (data.timeoutMS - (timeout.tv_sec * 1000)) * 1000;

		FD_ZERO(&data.descriptors);
		FD_SET(data.inputDescriptor, &data.descriptors);

		bool active = ::select(data.inputDescriptor + 1, &data.descriptors, 0, 0, &timeout);
		if (!active) 
		{
			return;
		}

		while (true) 
		{
			if (FD_ISSET(data.inputDescriptor, &data.descriptors) && PollInput()) 
			{
				return;
			}

			// TODO: implement on window resized
		}
	}

	bool PollInput() 
	{
		ssize_t readSize = 0;
		ssize_t targetSize = 64;
		std::vector<char> temporaryBuffer(targetSize, '\0');

		ssize_t currentSize = ::read(
			data.inputDescriptor,
			temporaryBuffer.data() + readSize,
			temporaryBuffer.size() - readSize
		);

		data.inputSequence += std::string(temporaryBuffer.data(), readSize);

		return readSize >= 0;
	}


	const std::string& GetInputSequence()
	{
		return data.inputSequence;
	}
}
