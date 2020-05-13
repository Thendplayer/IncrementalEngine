#pragma once
#include "EngineGame.h"
#include "Sprite.h"
#include "Text.h"
#include "Button.h"
#include "Tap.h"

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
		Sprite* _background;
		Tap* _tap;
		Text* _displayText;
	};
}
