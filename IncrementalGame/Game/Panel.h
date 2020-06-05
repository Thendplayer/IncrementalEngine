#pragma once

#include <Sprite.h>
#include <vector>
#include <Button.h>

using namespace IncrementalEngine;

namespace MagicIdle 
{
	class Panel : public Sprite
	{
	public:
		Panel();
		virtual ~Panel() override;

		virtual void Update() override;

		void SetValues(int elementsToShow, float distanceBetweenElements);
		void AddElement(Actor* actor);

		void MoveUp();
		void MoveDown();

	protected:
		Button* _upButton;
		Button* _downButton;
	
	private:
		vector<Actor*> _elements;

		int _elementsToShow;
		float _distanceBetweenElements;
		int _currentTopElement;

		bool _panelNeedsUpdate;
	};
}