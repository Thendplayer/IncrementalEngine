#include "Button.h"
#include "MainEngine.h"

namespace IncrementalEngine 
{
	void Button::Update()
	{
		Sprite::Update();

		_pressed = _released = false;

		float mouseX, mouseY;
		auto input = Engine::Get()->GetInput();
		input->GetMousePosition(mouseX, mouseY);

		if (_mousePosition.x != mouseX || _mousePosition.y != mouseY)
		{
			_mousePosition = D3DXVECTOR2(mouseX, mouseY);
			_mouseOver = MouseInsideBounds() && input->MouseInsideScreen();
		}

		if (input->IsMouseButtonDown(DirectInputMouseButton::MouseLeft))
		{
			if (!_clickDetected && _mouseOver)
			{
				_clickDetected = true;
				_pressed = true;
			}
		}
		else
		{
			if (_clickDetected)
			{
				_clickDetected = false;
				_released = true;
			}
		}
	}

	bool Button::Pressed()
	{
		return _pressed;
	}

	bool Button::Hold()
	{
		return _clickDetected;
	}

	bool Button::Released()
	{
		return _released;
	}
	
	bool Button::MouseInsideBounds()
	{
		FloatRect bounds = GetGlobalBounds();

		return _mousePosition.x > bounds.left() &&
			   _mousePosition.x < bounds.left() + bounds.width() &&
			   _mousePosition.y > bounds.top() &&
			   _mousePosition.y < bounds.top() + bounds.height();
	}
}