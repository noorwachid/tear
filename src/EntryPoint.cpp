#include "Tear/Session.h"
#include "Tear/Renderer.h"
#include "Tear/EventManager.h"

#include <iostream>
#include <thread>
#include <chrono>

std::string Pad(size_t count, size_t length = 6, char character = '0') 
{
	std::string t = std::to_string(count);
	std::string s(length - t.size(), character);

	return s + t;
}

int main() 
{
	Tear::Session session;
	auto sequence = session.GetSequence();

	session.Write(sequence->command.Move(1, 1) + "Hello World");
	session.Write(sequence->command.Move(2, 2) + "Hello World");

	std::this_thread::sleep_for(std::chrono::seconds(5));
}
