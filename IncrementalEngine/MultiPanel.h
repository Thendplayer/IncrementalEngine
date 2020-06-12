#pragma once

#include "Panel.h"
#include "Button.h"
#include <vector>

namespace IncrementalEngine 
{
	class MultiPanel : public Actor
	{
	public:
		MultiPanel();
		virtual ~MultiPanel() override;

		virtual void Update(float dt) override;

		void AddPair(
			Panel* panel, Button* button, 
			Texture* buttonSelectedTexture = nullptr, 
			Texture* buttonUnselectedTexture = nullptr
		);

	private:
		struct PanelButtonPair
		{
		public:
			Panel* Panel;
			Button* Button;
			Texture* ButtonSelectedTexture;
			Texture* ButtonUnselectedTexture;
		};

		vector<PanelButtonPair> _panelButtonPairs;
		int _selectedPanel;
	};
}