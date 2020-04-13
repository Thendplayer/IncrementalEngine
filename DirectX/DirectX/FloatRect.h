#ifndef _FLOAT_RECT_H
#define _FLOAT_RECT_H

#include <D2d1helper.h>

namespace MyEngine 
{
	struct FloatRect 
	{
	public:
		D2D1_RECT_F rect;
		
		FloatRect();
		FloatRect(float top, float left, float width, float height);

		float top() const;
		void top(float value);
		
		float left() const;
		void left(float value);
		
		float width() const;
		void width(float value);
		
		float height() const;
		void height(float value);
	};
}

#endif