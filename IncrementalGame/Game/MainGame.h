#pragma once

#include <EngineGame.h>
#include "ActionButton.h"
#include "DisplayPanel.h"
#include "UpgradesPerSecondPanel.h"
#include "MultiPanel.h"

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
		MultiPanel* _multiPanel;
		UpgradeElement* _upgradeElement;
	};
}