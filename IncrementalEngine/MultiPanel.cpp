#include "MultiPanel.h"

namespace IncrementalEngine
{
	MultiPanel::MultiPanel()
	{
		_panelButtonPairs = vector<PanelButtonPair>();
	}
	
	MultiPanel::~MultiPanel()
	{
		_panelButtonPairs.clear();
	}

	void MultiPanel::Update(float dt)
	{
		auto newSelectedPanel = -1;
		for (int i = 0; i < _panelButtonPairs.size(); i++)
		{
			if (_panelButtonPairs[i].Button->Pressed())
			{
				newSelectedPanel = i;
				break;
			}
		}

		if (newSelectedPanel != -1 && newSelectedPanel != _selectedPanel)
		{
			for (int i = 0; i < _panelButtonPairs.size(); i++)
			{
				bool isSelected = i == newSelectedPanel;
				_panelButtonPairs[i].Panel->SetActive(isSelected);
				
				if (_panelButtonPairs[i].ButtonSelectedTexture != nullptr &&
					_panelButtonPairs[i].ButtonUnselectedTexture != nullptr)
				{
					_panelButtonPairs[i].Button->SetTexture(isSelected ?
						_panelButtonPairs[i].ButtonSelectedTexture :
						_panelButtonPairs[i].ButtonUnselectedTexture
					);
				}
			}

			_selectedPanel = newSelectedPanel;
		}
	}
	
	void MultiPanel::AddPair(
		Panel* panel, 
		Button* button,
		Texture* buttonSelectedTexture,
		Texture* buttonUnselectedTexture
	)
	{
		bool firstPair = _panelButtonPairs.size() == 0;
		panel->SetActive(firstPair);

		if (buttonSelectedTexture != nullptr && buttonUnselectedTexture != nullptr)
		{
			button->SetTexture(firstPair ? buttonSelectedTexture : buttonUnselectedTexture);
		}

		_panelButtonPairs.push_back({
			panel, 
			button, 
			buttonSelectedTexture, 
			buttonUnselectedTexture
		});
	}
}