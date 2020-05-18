#pragma once

#include <EngineGame.h>

using namespace IncrementalEngine;

namespace MyGameNamespace 
{
	class MyGame : public EngineGame
	{
		virtual void Init() override;
		virtual void DeInit() override;
		virtual void Update(float dt) override;
	};
}