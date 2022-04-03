#pragma once

#include "Sequence.h"
#include "Node.h"

namespace Tear {
	class Term {
	public:
		static void run(Node* rootNode);

		static Node* getRootNode();
		static void setRootNode(Node* rootNode);
		static void destroyRootNode();

		static std::string getTerm();

	private:
		static void initialize();

		static void terminate();

		static void terminateWithError(const std::string& message);

	public:
		static void saveOriginalState();

		static void restoreOriginalState();

		static void write(const std::string& bytes);

	private:
		static void loop();

	private:
		static int ioDescriptor;

		static int windowResizedDescriptors[2];

		static std::string name;

		static Sequence sequence;

		static Node* rootNode;
		
		static bool running;
	};
}
