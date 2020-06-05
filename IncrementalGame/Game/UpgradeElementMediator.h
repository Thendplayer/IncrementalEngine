#pragma once

#include "Actor.h"
#include "UpgradeElementView.h"
#include "UpgradeElementModel.h"

using namespace IncrementalEngine;

namespace MagicIdle 
{
	class UpgradeElementMediator : public Actor
	{
	public:
		virtual ~UpgradeElementMediator() override;
		virtual void Init() override;
		virtual void Update(float dt) override;

		void SetCurrencyPtr(KmbNumber* currency);
		void SetValueToUpgradePtr(KmbNumber* value);
		void Upgrade();
		
		void SetValues(
			std::wstring& name, 
			Formula& costFormula, 
			Formula& upgradeFormula
		);

		UpgradeElementView* GetView();

	private:
		UpgradeElementModel* _model;
		UpgradeElementView* _view;

		KmbNumber* _valueToUpgrade;
		KmbNumber* _currency;
	};
}
