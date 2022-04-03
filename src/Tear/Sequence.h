#pragma once

#include <string>
#include <array>
#include "Key.h"

namespace Tear {
	struct Sequence {
		std::string caListener;
		std::string caExit;

		std::string keypadListener;
		std::string keypadExit;

		std::string mouseListener;
		std::string mouseExit;
	};

	struct OutputSequence {
		std::string cursorShown;
		std::string cursorHidden;

		std::string clear;
		std::string sgr0;
		std::string underlined;
		std::string bold;
		std::string blink;
		std::string reverse;
	};

	struct InputSequence {
		// not using unordered map because these guys
		// mostly used in iteration not lookup
		std::array<std::string, 22> keys;

		// lookup reference
		static constexpr std::array<Key, 22> referenceKeys = {
			Key::f1, Key::f2, Key::f3, Key::f4, 
			Key::f5, Key::f6, Key::f7, Key::f8, 
			Key::f9, Key::f10, Key::f11, Key::f12,

			Key::insert, Key::delete_, 
			Key::home, Key::end,
			Key::pageUp, Key::pageDown,

			Key::up, Key::down, Key::left, Key::right
		};
	};
}
