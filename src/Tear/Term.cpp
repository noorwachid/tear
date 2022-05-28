#include "Term.h"
#include "SequenceDatabase.h"

#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <iostream>

namespace Tear::Term
{
	struct TermData 
	{
		std::string name;
		bool open = true;
		int ioDescriptor = 0;
		int viewportDescriptors[2] = {0, 0};

		Sequence sequence;
		::termios previousState;
	};

	static TermData data;

	int GetWidth()
	{
		return 100;
	}

	int GetHeight()
	{
		return 80;
	}

	int GetIODescriptor() 
	{
		return data.ioDescriptor;
	}

	const std::string& GetName() 
	{
		return data.name;
	}

	const Sequence& GetSequence()
	{
		return data.sequence;
	}

	void Initialize() 
	{
		data.ioDescriptor = ::open("/dev/tty", O_RDWR);
		if (data.ioDescriptor < 0) 
		{
			TerminateWithError("Failed to open terminal IO");
		}

		const char* envTerm = ::getenv("TERM");
		if (!envTerm) 
		{
			TerminateWithError("No terminal is found");
		}

		data.name = envTerm;

		SequenceDatabase database(data.name);
		if (!database.exists()) 
		{
			TerminateWithError("Terminal is not supported");
		}

		data.sequence.Compose(data.name);
		
		int TermResult = pipe(data.viewportDescriptors);
		if (TermResult < 0) 
		{
			TerminateWithError("Failed to listen terminal container");
		}

		data.open = true;

		SavePreviousState();
	}

	void TerminateWithError(const std::string& message) 
	{
		Terminate();
		std::cout << message << "\n";
		std::exit(1);
	}

	void Terminate() 
	{
		RestorePreviousState();

		if (data.ioDescriptor > 0) 
		{
			::close(data.ioDescriptor);
		}
	}

	// Term Management System

	void SavePreviousState() 
	{
		::tcgetattr(data.ioDescriptor, &data.previousState);

		::termios currentState = data.previousState;
		// state.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL|IXON);
		// state.c_oflag &= ~(OPOST);
		// state.c_lflag &= ~(ECHO|ECHONL|ICANON|ISIG|IEXTEN);
		// state.c_cflag &= ~(CSIZE|PARENB);
		// state.c_cflag |= CS8;
		currentState.c_cc[VMIN] = 0;
		currentState.c_cc[VTIME] = 0;

		::tcsetattr(data.ioDescriptor, TCSAFLUSH, &currentState);

		Write(
			data.sequence.mode.caListener +
			data.sequence.command.cursorHidden +
			data.sequence.command.clear
		);
	}

	void RestorePreviousState() 
	{
		Write(
			data.sequence.command.cursorShown +
			data.sequence.command.sgr0 +
			data.sequence.command.clear +
			data.sequence.mode.caExit
		);

		::tcsetattr(data.ioDescriptor, TCSAFLUSH, &data.previousState);
	}
	
	void Close() 
	{
		data.open = false;
	}

	bool IsOpen() 
	{
		return data.open;
	}

	void Write(const std::string& buffer) 
	{
		::write(data.ioDescriptor, buffer.data(), buffer.size());
	}
}
