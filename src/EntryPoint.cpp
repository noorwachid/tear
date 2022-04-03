#include "Tear/Term.h"
#include "Tear/Renderer.h"
#include "Tear/EventManager.h"

using namespace Tear;

class RootNode: public Node {
	void onUpdate() {
		Renderer::clear();
		Renderer::setCursor(1, 1);
		Renderer::submit("😀 hi there!");

		Renderer::setCursor(1, 2);
		Renderer::submit(EventManager::inputBuffer);
	}
};

int main() {
	Term::run(new RootNode());
}
