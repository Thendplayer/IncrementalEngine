#include <cassert>

#include "WindowsInput.h"

namespace MyEngine 
{
	WindowsInput* WindowsInput::WINDOWS_INPUT = nullptr;

	WindowsInput::WindowsInput()
	{
		assert(WINDOWS_INPUT == nullptr && "trying to declarate two instances of WindowsInput class.");
		WINDOWS_INPUT = this;
	}
}