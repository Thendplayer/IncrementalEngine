#pragma once

#include <EngineGame.h>
#include "ActionButton.h"

using namespace IncrementalEngine;

namespace MagicIdle 
{
	class MainGame : public EngineGame
	{
	public:
		virtual void Init() override;
		virtual void DeInit() override;
		virtual void Update(float dt) override;

	private:
		ActionButton* _actionButton;
	};
}