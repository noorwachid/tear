#pragma once

#include "Frame.h"
#include "Sequence.h"
#include "Event.h"

namespace Tear {
	struct SessionState;

	class Session {
	public:
		Session();
		~Session();

	public:
		void close();
		bool isOpen() const { return open; }

		void write(const std::string& buffer);
		std::string read(size_t chuck = 64);

		int getDescriptor();
		const std::string& getTerm() const { return term; }
		const std::shared_ptr<Frame>& getFrame() const { return frame; }
		const std::shared_ptr<Sequence>& getSequence() const { return sequence; }

	private:
		void initialize();
		void terminate();
		void terminateWithError(const std::string& message);

		void restorePreviousState();
		void savePreviousState();

	private:
		bool open = true;
		int descriptor = 0;

		std::string term;
		std::shared_ptr<Frame> frame;
		std::shared_ptr<Sequence> sequence;
		SessionState* previousState;

		std::string inputBuffer;
		std::string outputBuffer;
	};
}
