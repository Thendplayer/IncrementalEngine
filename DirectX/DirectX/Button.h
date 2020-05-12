#ifndef _BUTTON_H
#define _BUTTON_H

#include "Sprite.h"

namespace MyEngine 
{
	class Button : public Sprite
	{
	public:
		virtual void Update() override;

		bool Pressed();
		bool Hold();
		bool Released();

	private:
		D3DXVECTOR2 _mousePosition;
		bool _clickDetected;
		bool _mouseOver;

		bool _pressed;
		bool _released;

		bool MouseInsideBounds();
	};
}

#endif