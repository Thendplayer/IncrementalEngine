#include "FloatRect.h"

namespace MyEngine 
{
	FloatRect::FloatRect()
	{
		rect = D2D1_RECT_F{ 0, 0, 0, 0 };
	}

	FloatRect::FloatRect(float top, float left, float width, float height)
	{
		rect = D2D1_RECT_F{ top, left, height, width };
	}

	float FloatRect::top() const
	{
		return rect.top;
	}
	
	void FloatRect::top(float value)
	{
		rect.top = value;
	}
	
	float FloatRect::left() const
	{
		return rect.left;
	}
	
	void FloatRect::left(float value)
	{
		rect.left = value;
	}
	
	float FloatRect::width() const
	{
		return rect.right;
	}
	
	void FloatRect::width(float value)
	{
		rect.right = value;
	}
	
	float FloatRect::height() const
	{
		return rect.bottom;
	}
	
	void FloatRect::height(float value)
	{
		rect.bottom = value;
	}
}
