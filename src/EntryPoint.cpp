#include "Tear/Term.h"
#include "Tear/Renderer.h"
#include "Tear/EventManager.h"

using namespace Tear;

int main() 
{
	Term::Initialize();
	EventManager::Initialize();
	Renderer::Initialize();

	size_t frameCount = 0;
	
	while (Term::IsOpen() && frameCount < 10) 
	{
		++frameCount;

		Renderer::Set(0, 0, "frameCount: " + std::to_string(frameCount));
		Renderer::Set(0, 1, "😀 smile!");
		Renderer::Set(0, 2, EventManager::GetInputSequence());
		Renderer::Flush();

		EventManager::Poll();
	}

	Term::Terminate();
}
