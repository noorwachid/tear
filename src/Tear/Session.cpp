#include "Session.h"
#include "SequenceDatabase.h"
#include <vector>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <iostream>
#include <sys/select.h>
#include <unistd.h>

namespace Tear {
	struct SessionState {
		::termios data;
	};

	Session::Session() {
		initialize();
	}

	Session::~Session() {
		terminate();
	}

	void Session::initialize() {
		descriptor = ::open("/dev/tty", O_RDWR);
		if (descriptor < 0) 
			terminateWithError("Failed to open descriptor");

		const char* envTerm = ::getenv("TERM");
		if (!envTerm) 
			terminateWithError("No terminal is found");

		term = envTerm;
		
		frame = std::make_shared<Frame>();
		if (!frame) 
			terminateWithError("Failed to listen frame descriptor");

		SequenceDatabase sequenceDatabase(term);
		sequence = sequenceDatabase.get();
		if (!sequence) 
			terminateWithError("Terminal is not supported");

		open = true;

		savePreviousState();
	}

	void Session::terminateWithError(const std::string& message) {
		terminate();
		std::cout << message << "\n";
		std::exit(1);
	}

	void Session::terminate() {
		restorePreviousState();

		if (descriptor > 0) 
			::close(descriptor);
	}

	// Term Management System

	void Session::savePreviousState() {
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

		write(
			sequence->mode.enterCa +
			sequence->command.hideCursor +
			sequence->command.clear
		);
	}

	void Session::restorePreviousState() {
		write(
			sequence->command.showCursor +
			sequence->command.reset +
			sequence->command.clear +
			sequence->mode.exitCa
		);

		::tcsetattr(descriptor, TCSAFLUSH, &previousState->data);
	}
	
	void Session::close() {
		open = false;
	}

	void Session::write(const std::string& buffer) {
		::write(descriptor, buffer.data(), buffer.size());
	}

	std::string Session::read(size_t chunk) {
		std::vector<char> buffer(chunk, 0);

		ssize_t byteRead = ::read(
			descriptor,
			buffer.data(),
			buffer.size()
		);

		return std::string(buffer.data(), byteRead);
	}
}
