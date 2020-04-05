#pragma once
#include "EngineGame.h"
#include "Bitmap.h"

using namespace MyEngine;

namespace MyGame
{
	class ExampleGame : public EngineGame
	{
	public:
		Bitmap* bitmap;
		float x;
		float y;

		void Init() override;
		void DeInit() override;
		void Update(float dt) override;

		ExampleGame();
	protected:
		~ExampleGame();
	};
}
