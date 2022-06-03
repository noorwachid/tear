#pragma once

#include <string>
#include <array>
#include "Key.h"

namespace Tear 
{
	struct ModeSequence 
	{
		std::string enterCa;
		std::string exitCa;

		std::string enterKeypad;
		std::string exitKeypad;

		std::string enterMouse;
		std::string exitMouse;
	};

	struct CommandSequence 
	{
		std::string showCursor;
		std::string hideCursor;

		std::string clear;
		std::string reset;
		std::string underlined;
		std::string bold;
		std::string blink;
		std::string reverse;

		std::string MoveCursor(int x, int y) const 
		{
			return "\033[" + std::to_string(y + 1) + ";" + std::to_string(x + 1) + "H";
		}
	};

	struct KeySequence 
	{
		// not using unordered map because these guys
		// mostly used in iteration not lookup
		std::array<std::string, 22> data;

		// lookup reference
		static constexpr std::array<Key, 22> references = {
			Key::F1, Key::F2, Key::F3, Key::F4, 
			Key::F5, Key::F6, Key::F7, Key::F8, 
			Key::F9, Key::F10, Key::F11, Key::F12,

			Key::Insert, Key::Delete, 
			Key::Home, Key::End,
			Key::PageUp, Key::PageDown,

			Key::Up, Key::Down, Key::Left, Key::Right
		};
	};

	struct Sequence 
	{
		ModeSequence mode;
		CommandSequence command;
		KeySequence key;
	};
}
