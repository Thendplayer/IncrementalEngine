#pragma once

#include "Button.h"
#include "Text.h"

using namespace IncrementalEngine;

namespace MyGame
{
	class Tap : public Actor
	{
	public:
		virtual void Init() override;
		virtual void Update() override;

		int GetValue();

	private:
		Button* _button;
		Text* _text;
		int _value;
	};
}