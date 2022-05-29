#include "Tear/Session.h"
#include "Tear/Renderer.h"
#include "Tear/EventManager.h"

#include <iostream>

std::string pad(size_t count, size_t length = 6, char character = '0') {
	std::string t = std::to_string(count);
	std::string s(length - t.size(), character);

	return s + t;
}

int main() {
	Tear::Session session;
	Tear::Renderer renderer(session.getSequence(), 100, 80);
	
	for (size_t frameCount = 0; frameCount < 100000 && session.isOpen(); ++frameCount) {
		// renderer.set(0, 0, "Hello World");
		// renderer.swapBuffers();

		// session.write(renderer.getBuffer());

		session.write("hello");
	}
}
