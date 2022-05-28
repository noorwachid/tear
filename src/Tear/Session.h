#pragma once

#include "Sequence.h"
#include "Node.h"

namespace Tear {
	struct State;
	
	class Session {
	public:
		Session();
		~Session();

		std::string getTerm();

	private:
		void initialize();
		void terminate();
		void terminateWithError(const std::string& message);

	public:
		void savePreviousState();
		void restorePreviousState();

		void close();
		bool isOpen();

		void write(const std::string& buffer);

	public:
		Sequence sequence;

	private:
		bool open = true;

	public:
		int ioDescriptor = 0;
		int sessionResizedDescriptors[2] = {0, 0};

		std::string name;
		State* previousState;
	};
}
