#include "Session.h"
#include "SequenceDatabase.h"
#include "EventManager.h"

#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <iostream>

namespace Tear {
	struct State {
		::termios data;
	};

	Session::Session() {
		initialize();
	}

	Session::~Session() {
		terminate();
	}

	std::string Session::getTerm() {
		return name;
	}

	void Session::initialize() {
		ioDescriptor = ::open("/dev/tty", O_RDWR);
		if (ioDescriptor < 0) {
			terminateWithError("Failed to open terminal IO");
		}

		const char* envTerm = ::getenv("TERM");
		if (!envTerm) {
			terminateWithError("No terminal is found");
		}

		name = envTerm;

		SequenceDatabase database(name);
		if (!database.exists()) {
			terminateWithError("Terminal is not supported");
		}

		sequence.compose(name);

		EventManager::initialize(ioDescriptor);
		
		int sessionResult = pipe(sessionResizedDescriptors);
		if (sessionResult < 0) {
			terminateWithError("Failed to listen terminal container");
		}

		open = true;

		previousState = new State();
		savePreviousState();
	}

	void Session::terminateWithError(const std::string& message) {
		terminate();
		std::cout << message << "\n";
		std::exit(1);
	}

	void Session::terminate() {
		restorePreviousState();

		if (previousState) {
			delete previousState;
			previousState = nullptr;
		}

		if (ioDescriptor > 0) {
			::close(ioDescriptor);
		}
	}

	// Session Management System

	void Session::savePreviousState() {
		::tcgetattr(ioDescriptor, &previousState->data);

		::termios state = previousState->data;
		// state.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL|IXON);
		// state.c_oflag &= ~(OPOST);
		// state.c_lflag &= ~(ECHO|ECHONL|ICANON|ISIG|IEXTEN);
		// state.c_cflag &= ~(CSIZE|PARENB);
		// state.c_cflag |= CS8;
		state.c_cc[VMIN] = 0;
		state.c_cc[VTIME] = 0;

		::tcsetattr(ioDescriptor, TCSAFLUSH, &state);

		write(
			sequence.mode.caListener +
			sequence.command.cursorHidden +
			sequence.command.clear
		);
	}

	void Session::restorePreviousState() {
		write(
			sequence.command.cursorShown +
			sequence.command.sgr0 +
			sequence.command.clear +
			sequence.mode.caExit
		);

		::tcsetattr(ioDescriptor, TCSAFLUSH, &previousState->data);
	}
	
	void Session::close() {
		open = false;
	}

	bool Session::isOpen() {
		return open;
	}

	void Session::write(const std::string& buffer) {
		::write(ioDescriptor, buffer.data(), buffer.size());
	}
}
