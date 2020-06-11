#pragma once

#include <Button.h>
#include <Sound.h>

using namespace IncrementalEngine;

namespace MagicIdle 
{
	class ActionButtonView : public Button
	{
	public:
		virtual void Init() override;
		virtual void Update(float dt) override;

	private:
		Sprite* _pressedSprite;
		Sound* _buttonSound;
	};
}
