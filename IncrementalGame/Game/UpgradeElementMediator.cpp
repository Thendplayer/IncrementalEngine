#include "UpgradeElementMediator.h"
#include <MainEngine.h>

namespace MagicIdle 
{
	UpgradeElementMediator::~UpgradeElementMediator()
	{
		delete _model;
	}
	
	void UpgradeElementMediator::Init()
	{
		_view = Engine::Get()->Scene()->Create<UpgradeElementView>();
		_model = new UpgradeElementModel();
	}

	void UpgradeElementMediator::Update(float dt)
	{
		bool available = _model->IsAvailable(*_currency);
		_view->SetAvailability(available);

		if (_view->Pressed() && available)
		{
			_currency->Subtract(_model->GetCost());
			_totalSpent->Add(_model->GetCost());
			_valueToUpgrade->Add(_model->GetUpgrade());
			Upgrade();

			Engine::Get()->Audio()->Play(Engine::Get()->Resources()->GetSound("UpgradeSound"));
		}
	}
	
	void UpgradeElementMediator::SetCurrencyPtrs(KmbNumber* currency, KmbNumber* totalSpent)
	{
		_currency = currency;
		_totalSpent = totalSpent;
	}

	void UpgradeElementMediator::SetValueToUpgradePtr(KmbNumber* value)
	{
		_valueToUpgrade = value;
	}

	void UpgradeElementMediator::Upgrade()
	{
		_model->LevelUp();

		std::wstring cost = _model->GetCost().ToString();
		std::wstring upgrade = _model->GetUpgrade().ToString() + _upgradeSuffix;

		_view->SetValues(_model->GetLevel(), cost, upgrade);
	}

	void UpgradeElementMediator::SetValues(
		std::wstring& name,
		Formula& upgradeFormula,
		Formula& costFormula,
		std::wstring upgradeSuffix
	)
	{
		_upgradeSuffix = upgradeSuffix;
		_model->SetValues(name, costFormula, upgradeFormula);

		std::wstring cost = _model->GetCost().ToString();
		std::wstring upgrade = _model->GetUpgrade().ToString() + _upgradeSuffix;
		
		_view->SetName(name);
		_view->SetValues(_model->GetLevel(), cost, upgrade);
	}
	
	UpgradeElementView* UpgradeElementMediator::GetView()
	{
		return _view;
	}
}