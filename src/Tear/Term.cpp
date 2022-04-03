#include "Term.h"
#include "SequenceManager.h"
#include "Renderer.h"
#include "EventManager.h"

#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <iostream>

namespace Tear {

	int Term::ioDescriptor;
	int Term::windowResizedDescriptors[2];

	std::string Term::name;

	Sequence Term::sequence;

	bool Term::running = false;

	Node* Term::rootNode = nullptr;

	void Term::run(Node* node) {
		initialize();
		saveOriginalState();

		setRootNode(node);

		loop();

		destroyRootNode();

		restoreOriginalState();
		terminate();
	}

	Node* Term::getRootNode() {
		return rootNode;
	}

	void Term::setRootNode(Node* rootNode) {
		destroyRootNode();
	
		Term::rootNode = rootNode;
		Term::rootNode->onCreate();
	}

	void Term::destroyRootNode() {
		if (rootNode) {
			rootNode->onDestroy();
			delete rootNode;
			rootNode = nullptr;
		}
	}

	std::string Term::getTerm() {
		return name;
	}

	void Term::initialize() {
		ioDescriptor = ::open("/dev/tty", O_RDWR);
		if (ioDescriptor < 0) {
			terminateWithError("Failed to open terminal IO");
		}

		const char* envTerm = ::getenv("TERM");
		if (!envTerm) {
			terminateWithError("No terminal is found");
		}

		name = envTerm;

		SequenceManager sequenceManager(name);
		if (!sequenceManager.exists()) {
			terminateWithError("Terminal is not supported");
		}

		sequence = sequenceManager.compose();

		Renderer::initialize(ioDescriptor, sequenceManager.composeOutput());

		EventManager::initialize(ioDescriptor);
		
		int windowResult = pipe(windowResizedDescriptors);
		if (windowResult < 0) {
			terminateWithError("Failed to listen terminal container");
		}

		running = true;
	}

	void Term::terminateWithError(const std::string& message) {
		terminate();
		std::cout << message << "\n";
		std::exit(1);
	}

	void Term::terminate() {
		if (ioDescriptor > 0) {
			::close(ioDescriptor);
		}
	}

	// Session Management System

	::termios originalState;

	void Term::saveOriginalState() {
		::tcgetattr(ioDescriptor, &originalState);

		::termios state = originalState;
		// state.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL|IXON);
		// state.c_oflag &= ~(OPOST);
		// state.c_lflag &= ~(ECHO|ECHONL|ICANON|ISIG|IEXTEN);
		// state.c_cflag &= ~(CSIZE|PARENB);
		// state.c_cflag |= CS8;
		state.c_cc[VMIN] = 0;
		state.c_cc[VTIME] = 0;

		::tcsetattr(ioDescriptor, TCSAFLUSH, &state);

		Renderer::submit(sequence.caListener);
		Renderer::hideCursor();
		Renderer::clear();
	}

	void Term::restoreOriginalState() {
		Renderer::showCursor();
		Renderer::reset();
		Renderer::clear();
		Renderer::submit(sequence.caExit);

		::tcsetattr(ioDescriptor, TCSAFLUSH, &originalState);
	}

	// Main Loop System
	
	void Term::loop() {
		while (running) {
			if (rootNode) {
				rootNode->onUpdate();
			}

			EventManager::poll();
		}
	}
}
