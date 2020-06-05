#pragma once

#include <EngineGame.h>

#include "ActionButtonMediator.h"
#include "DisplayPanelMediator.h"

#include "UpgradesPanel.h"
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
		Button* _upgradesPerSecondButton;
		Button* _upgradesPerClickButton;
		
		ActionButtonMediator* _actionButton;
		DisplayPanelMediator* _displayPanel;
		
		MultiPanel* _multiPanel;
	};
}