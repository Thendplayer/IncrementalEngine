#pragma once

#include "Panel.h"
#include "UpgradeElement.h"

using namespace IncrementalEngine;

namespace MagicIdle 
{
	class UpgradesPerSecondPanel : public Panel
	{
	public:
		virtual void Init() override;
		Button* GetPanelButton();

	private:
		Button* _panelButton;
	};
}
