#pragma once

#include <Text.h>
#include <Button.h>
#include <KmbNumber.h>

#include "Formula.h"

using namespace IncrementalEngine;

namespace MagicIdle
{
	class UpgradeElementView : public Button
	{
	public:
		virtual void Init() override;
		virtual void Update(float dt) override;

		void SetAvailability(bool available);
		void SetName(std::wstring& name);

		void SetValues(
			int level,
			std::wstring& cost,
			std::wstring& upgrade
		);

	private:
		Text* _nameText;
		Text* _upgradeText;
		Text* _levelText;
		Text* _costText;

		Sprite* _sprite;
		Sprite* _foreground;
	};
}
