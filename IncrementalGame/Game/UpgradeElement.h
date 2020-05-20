#pragma once

#include <Text.h>
#include <Button.h>
#include "KmbNumber.h"

using namespace IncrementalEngine;

namespace MagicIdle
{
	class UpgradeElement : public Button
	{
	public:
		virtual void Init() override;
		virtual void Update() override;

		void SetValues(
			std::wstring name, 
			KmbNumber& upgrade, 
			KmbNumber& cost, 
			int level
		);

		bool SetAvailability(KmbNumber& currency);

	private:
		Text* _name;
		Text* _upgrade;
		Text* _level;
		Text* _cost;

		Sprite* _sprite;
		Sprite* _foreground;

		KmbNumber& _costValue = KmbNumber::Zero;
	};
}
