#include "FloatRect.h"

namespace MyEngine 
{
	FloatRect::FloatRect()
	{
		rect = D2D1_RECT_F{ 0, 0, 0, 0 };
	}

	FloatRect::FloatRect(float left, float top, float width, float height)
	{
		rect = D2D1_RECT_F{ left, top, width, height };
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
	
	D2D1_RECT_F FloatRect::GetRect()
	{
		D2D1_RECT_F rc = {
			rect.left,
			rect.top,
			rect.left + rect.right,
			rect.top + rect.bottom
		};

		return rc;
	}

	bool operator ==(const FloatRect& left, const FloatRect& right)
	{
		return (
			left.top() == right.top() &&
			left.left() == right.left() &&
			left.height() == right.height() &&
			left.width() == right.width()
		);
	}

	bool operator !=(const FloatRect& left, const FloatRect& right)
	{
		return !(left == right);
	}
}
