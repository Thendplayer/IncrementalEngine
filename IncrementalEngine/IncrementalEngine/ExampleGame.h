#pragma once
#include "EngineGame.h"
#include "Sprite.h"
#include "Text.h"
#include "Button.h"

using namespace IncrementalEngine;

namespace MyGame
{
	class ExampleGame : public EngineGame
	{
	public:
		void Init() override;
		void DeInit() override;
		void Update(float dt) override;
	
	private:
		Sprite* _sprite;
		Button* _button;
		Sprite* _child;
		Text* _text;
	};
}
