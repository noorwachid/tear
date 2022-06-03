#include "Session.h"
#include "SequenceDatabase.h"
#include <vector>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <iostream>
#include <sys/select.h>
#include <unistd.h>

namespace Tear 
{
	void RestorePreviousState();
	void SavePreviousState();

	struct SessionState 
	{
		::termios data;
	};

	Session::Session() 
	{
		Initialize();
	}

	Session::~Session() 
	{
		Terminate();
	}

	void Session::Initialize() 
	{
		descriptor = ::open("/dev/tty", O_RDWR);
		if (descriptor < 0) 
			TerminateWithError("Failed to open descriptor");

		const char* envTerm = ::getenv("TERM");
		if (!envTerm) 
			TerminateWithError("No terminal is found");

		term = envTerm;
		
		frame = std::make_shared<Frame>();
		if (!frame) 
			TerminateWithError("Failed to listen frame descriptor");

		SequenceDatabase sequenceDatabase(term);
		sequence = sequenceDatabase.get();
		if (!sequence) 
			TerminateWithError("Terminal is not supported");

		open = true;

		SavePreviousState();
	}

	void Session::TerminateWithError(const std::string& message) 
	{
		Terminate();
		std::cout << message << "\n";
		std::exit(1);
	}

	void Session::Terminate() 
	{
		RestorePreviousState();

		if (descriptor > 0) 
			::close(descriptor);
	}

	// Term Management System

	void Session::SavePreviousState() 
	{
		::tcgetattr(descriptor, &previousState->data);

		::termios currentState = previousState->data;
		currentState.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL|IXON);
		currentState.c_oflag &= ~(OPOST);
		currentState.c_lflag &= ~(ECHO|ECHONL|ICANON|ISIG|IEXTEN);
		currentState.c_cflag &= ~(CSIZE|PARENB);
		currentState.c_cflag |= CS8;
		currentState.c_cc[VMIN] = 0;
		currentState.c_cc[VTIME] = 0;

		::tcsetattr(descriptor, TCSAFLUSH, &currentState);

		Write(
			sequence->mode.enterCa +
			sequence->command.hideCursor +
			sequence->command.clear
		);
	}

	void Session::RestorePreviousState() 
	{
		Write(
			sequence->command.showCursor +
			sequence->command.reset +
			sequence->command.clear +
			sequence->mode.exitCa
		);

		::tcsetattr(descriptor, TCSAFLUSH, &previousState->data);
	}
	
	void Session::Close() 
	{
		open = false;
	}

	void Session::Write(const std::string& buffer) 
	{
		::write(descriptor, buffer.data(), buffer.size());
	}

	std::string Session::Read(size_t chunk) 
	{
		std::vector<char> buffer(chunk, 0);

		ssize_t byteRead = ::read(
			descriptor,
			buffer.data(),
			buffer.size()
		);

		return std::string(buffer.data(), byteRead);
	}
}
