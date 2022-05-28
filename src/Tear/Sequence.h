#pragma once

#include <string>
#include <array>
#include "Key.h"

namespace Tear {
	struct ModeSequence {
		std::string caListener;
		std::string caExit;

		std::string keypadListener;
		std::string keypadExit;

		std::string mouseListener;
		std::string mouseExit;
	};

	struct CommandSequence {
		std::string cursorShown;
		std::string cursorHidden;

		std::string clear;
		std::string sgr0;
		std::string underlined;
		std::string bold;
		std::string blink;
		std::string reverse;

		std::string move(int x, int y) {
			return "\033[" + std::to_string(y + 1) + ";" + std::to_string(x + 1) + "H";
		}
	};

	struct KeySequence {
		// not using unordered map because these guys
		// mostly used in iteration not lookup
		std::array<std::string, 22> data;

		// lookup reference
		static constexpr std::array<Key, 22> references = {
			Key::f1, Key::f2, Key::f3, Key::f4, 
			Key::f5, Key::f6, Key::f7, Key::f8, 
			Key::f9, Key::f10, Key::f11, Key::f12,

			Key::insert, Key::delete_, 
			Key::home, Key::end,
			Key::pageUp, Key::pageDown,

			Key::up, Key::down, Key::left, Key::right
		};
	};

	struct Sequence {
		ModeSequence mode;
		CommandSequence command;
		KeySequence key;

		void compose(const std::string& term);
	};
}
