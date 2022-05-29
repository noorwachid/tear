#include "Core.h"
#include "SequenceDatabase.h"
#include <vector>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <iostream>
#include <sys/select.h>
#include <unistd.h>

namespace Tear {
	// forward declarations
	void restorePreviousState();
	void savePreviousState();

	struct CoreData {
		std::string name;
		bool open = true;
		int ioDescriptor = 0;
		int viewportDescriptors[2] = {0, 0};

		Sequence sequence;
		::termios previousState;

		std::string inputBuffer;
		std::string outputBuffer;

		::fd_set descriptors;
	};

	static CoreData data;

	int getFrameWidth() {
		return 100;
	}

	int getFrameHeight() {
		return 80;
	}

	int getIODescriptor() {
		return data.ioDescriptor;
	}

	const std::string& getTerm() {
		return data.name;
	}

	const Sequence& getSequence() {
		return data.sequence;
	}

	void initializeEvents() {
		FD_ZERO(&data.descriptors);
		FD_SET(data.ioDescriptor, &data.descriptors);
	}

	void initialize() {
		data.ioDescriptor = ::open("/dev/tty", O_RDWR);
		if (data.ioDescriptor < 0) 
			terminateWithError("Failed to open terminal IO");

		const char* envTerm = ::getenv("TERM");
		if (!envTerm) 
			terminateWithError("No terminal is found");

		data.name = envTerm;
		SequenceDatabase database(data.name);
		if (!database.exists()) 
			terminateWithError("Terminal is not supported");

		data.sequence.compose(data.name);
		
		int TermResult = pipe(data.viewportDescriptors);
		if (TermResult < 0) 
			terminateWithError("Failed to listen terminal container");

		data.open = true;

		savePreviousState();

		initializeEvents();
	}

	void terminateWithError(const std::string& message) {
		terminate();
		std::cout << message << "\n";
		std::exit(1);
	}

	void terminate() {
		restorePreviousState();

		if (data.ioDescriptor > 0) 
			::close(data.ioDescriptor);
	}

	// Term Management System

	void savePreviousState() {
		::tcgetattr(data.ioDescriptor, &data.previousState);

		::termios currentState = data.previousState;
		currentState.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL|IXON);
		currentState.c_oflag &= ~(OPOST);
		currentState.c_lflag &= ~(ECHO|ECHONL|ICANON|ISIG|IEXTEN);
		currentState.c_cflag &= ~(CSIZE|PARENB);
		currentState.c_cflag |= CS8;
		currentState.c_cc[VMIN] = 0;
		currentState.c_cc[VTIME] = 0;

		::tcsetattr(data.ioDescriptor, TCSAFLUSH, &currentState);

		write(
			data.sequence.mode.enterCa +
			data.sequence.command.hideCursor +
			data.sequence.command.clear
		);
	}

	void restorePreviousState() {
		write(
			data.sequence.command.showCursor +
			data.sequence.command.reset +
			data.sequence.command.clear +
			data.sequence.mode.exitCa
		);

		::tcsetattr(data.ioDescriptor, TCSAFLUSH, &data.previousState);
	}
	
	void close() {
		data.open = false;
	}

	bool isOpen() {
		return data.open;
	}

	void write(const std::string& buffer) {
		::write(data.ioDescriptor, buffer.data(), buffer.size());
	}

	std::string read(size_t chunk) {
		std::vector<char> buffer(chunk, 0);

		ssize_t byteRead = ::read(
			data.ioDescriptor,
			buffer.data(),
			buffer.size()
		);

		return std::string(buffer.data(), byteRead);
	}
}
