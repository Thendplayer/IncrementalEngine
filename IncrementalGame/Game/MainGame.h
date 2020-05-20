#pragma once

#include <EngineGame.h>
#include "ActionButton.h"
#include "DisplayPanel.h"
#include "UpgradeElement.h"

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
		DisplayPanel* _displayPanel;
		UpgradeElement* _upgradeElement;
	};
}