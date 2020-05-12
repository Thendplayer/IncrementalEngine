#ifndef _FLOAT_RECT_H
#define _FLOAT_RECT_H

#include <D2d1helper.h>

namespace IncrementalEngine 
{
	struct FloatRect 
	{
	public:
		FloatRect();
		FloatRect(float left, float top, float width, float height);

		float top() const;
		void top(float value);
		
		float left() const;
		void left(float value);
		
		float width() const;
		void width(float value);
		
		float height() const;
		void height(float value);
		
		D2D1_RECT_F GetRect();

	private:
		D2D1_RECT_F rect;
	};

	bool operator ==(const FloatRect& left, const FloatRect& right);
	bool operator !=(const FloatRect& left, const FloatRect& right);
}

#endif