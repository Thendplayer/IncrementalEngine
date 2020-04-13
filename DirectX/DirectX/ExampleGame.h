#pragma once
#include "EngineGame.h"
#include "Actor.h"

using namespace MyEngine;

namespace MyGame
{
	class ExampleGame : public EngineGame
	{
	public:
		void Init() override;
		void DeInit() override;
		void Update(float dt) override;
	
	private:
		Actor* _actor;
	};
}
