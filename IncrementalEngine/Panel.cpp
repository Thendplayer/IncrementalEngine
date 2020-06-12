#include "Panel.h"

namespace IncrementalEngine
{
	Panel::Panel()
	{
		_elements = vector<Actor*>();
	}

	Panel::~Panel()
	{
		_elements.clear();
	}
	
	void Panel::Update(float dt)
	{
		Sprite::Update(dt);

		if (_upButton->Pressed())
		{
			MoveUp();
		}

		if (_downButton->Pressed())
		{
			MoveDown();
		}

		if (_panelNeedsUpdate) 
		{
			SetOrigin(GetOrigin().x, 0);

			D3DXVECTOR2 pos = D3DXVECTOR2(0, -_distanceBetweenElements);
			for (int i = 0; i < _elements.size(); i++)
			{
				if (i < _currentTopElement || i >= _currentTopElement + _elementsToShow)
				{
					_elements[i]->SetActive(false);
					continue;
				}

				pos = {
					pos.x,
					pos.y + _distanceBetweenElements + _elements[i]->GetLocalBounds().height()
				};

				_elements[i]->SetPosition(pos);
				_elements[i]->SetActive(true);
			}

			_panelNeedsUpdate = false;
		}
	}

	void Panel::SetValues(int elementsToShow, float distanceBetweenElements)
	{
		_elementsToShow = elementsToShow;
		_distanceBetweenElements = distanceBetweenElements;

		_panelNeedsUpdate = true;
	}

	void Panel::AddElement(Actor* actor)
	{
		if (std::find(_elements.begin(), _elements.end(), actor) != _elements.end())
		{
			return;
		}

		actor->SetParent(this);
		_elements.push_back(actor);

		_panelNeedsUpdate = true;
	}
	
	void Panel::MoveUp()
	{
		if (_currentTopElement > 0)
		{
			_currentTopElement--;
			_panelNeedsUpdate = true;
		}
	}
	
	void Panel::MoveDown()
	{
		if (_currentTopElement < _elements.size() - _elementsToShow)
		{
			_currentTopElement++;
			_panelNeedsUpdate = true;
		}
	}
}