#pragma once

#include "Frame.h"
#include "Sequence.h"
#include "Event.h"

namespace Tear 
{
	struct SessionState;

	class Session 
	{
	public:
		Session();
		~Session();

	public:
		void Close();
		bool IsOpen() const { return open; }

		void Write(const std::string& buffer);
		std::string Read(size_t chuck = 64);

		int GetDescriptor();
		const std::string& GetTerm() const { return term; }
		const std::shared_ptr<Frame>& GetFrame() const { return frame; }
		const std::shared_ptr<Sequence>& GetSequence() const { return sequence; }

	private:
		void Initialize();
		void Terminate();
		void TerminateWithError(const std::string& message);

		void RestorePreviousState();
		void SavePreviousState();

	private:
		bool open = true;
		int descriptor = 0;

		std::string term;
		std::shared_ptr<Frame> frame;
		std::shared_ptr<Sequence> sequence;
		std::shared_ptr<SessionState> previousState;

		std::string inputBuffer;
		std::string outputBuffer;
	};
}
