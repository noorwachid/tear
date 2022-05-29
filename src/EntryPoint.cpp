#include "Tear/Core.h"
#include "Tear/Renderer.h"
#include "Tear/EventManager.h"

#include <iostream>

std::string pad(size_t count, size_t length = 6, char character = '0') {
	std::string t = std::to_string(count);
	std::string s(length - t.size(), character);

	return s + t;
}

class Scene {
public:
	void update() {
		++frameCount;

		if (frameCount > 100000) {
			Tear::close();
		}

		Tear::Renderer::set(0, 0, "FrameCount: " + pad(frameCount));
	}

private:
	size_t frameCount = 0;
};

int main() {
	Tear::initialize();
	Tear::Renderer::initialize();

	std::shared_ptr<Scene> scene = std::make_shared<Scene>();

	while (Tear::isOpen()) {
		if (scene)
			scene->update();

		Tear::Renderer::swapBuffers();
	}

	Tear::terminate();
}
