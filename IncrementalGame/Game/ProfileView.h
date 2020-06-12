#pragma once

#include <Sprite.h>
#include <Button.h>
#include <Text.h>

using namespace IncrementalEngine;

namespace MagicIdle 
{
	class ProfileView : public Sprite
	{
	public:
		virtual void Init() override;
		virtual void Update(float dt) override;

		void SetValues(
			std::wstring totalEarned, 
			std::wstring totalSpent, 
			std::wstring totalTaps
		);

	private: 
		Button* _closeButton;
		Button* _creditsButton;
		Button* _exitButton;

		Text* _totalEarnedText;
		Text* _totalSpentText;
		Text* _totalTapsText;

		Sprite* _creditsSprite;
	};
}